#include "aepch.h"
#include "Model.h"
#include "glad/glad.h"
#include "Anomaly/Rendering/stb_image.h"


namespace Anomaly
{
	void Model::Draw(std::shared_ptr<Shader> shader)
	{
		for(auto i = 0; i < m_meshes.size();i++)
			m_meshes[i].Draw(shader);
		
	}

	void Model::loadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene *Scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if(!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
		{
			AE_CORE_ERROR("Failed to import model! : {0}", importer.GetErrorString());
			return;
		}

		m_directory = path.substr(0, path.find_last_of('/'));

		processNode(Scene->mRootNode, Scene);
		
	}

	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		//Processes imported meshes
		for(auto i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(processMesh(mesh, scene));
		}

		//Processes children of imported meshes
		for(auto i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		//This processes the vertices-------------------------------------------
		for(auto i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			//Processes meshes position
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			//Processes meshes normal
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Position = vector;

			//Processes meshes TexCoords
			if(mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.f,0.f);
			}
			vertices.push_back(vertex);
		}
		//----------------------------------------------------------------------

		//Processes Indices-----------------------------------------------------
		for (auto i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (auto j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		//----------------------------------------------------------------------

		//Processes Materials---------------------------------------------------
		if(mesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<Texture> diffusemaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffusemaps.begin(), diffusemaps.end());

			std::vector<Texture> specularmaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularmaps.begin(), specularmaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;
		for(auto i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString aiStr;
			mat->GetTexture(type, i, &aiStr);
			bool skiploading = false;
			for(auto j = 0; j < m_TexturesLoaded.size(); j++)
			{
				textures.push_back(m_TexturesLoaded[j]);
				skiploading = true;
				break;
			}

			if(!skiploading)
			{
				Texture texture;
				//texture.id = TextureFromFile(aiStr.C_str(), m_directory);
				texture.type = typeName;
				texture.path = aiStr.C_Str();
				textures.push_back(texture);
				m_TexturesLoaded.push_back(texture);
			}			
		}
		return textures;
	}

	unsigned int Model::TextureFromFile(const char* path, const std::string& directory, bool gamma)
	{
		std::string filename(path);
		filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width,height,ncomponents;
		unsigned char *data = stbi_load(filename.c_str(), &width, &height, &ncomponents, 0);

		if(data)
		{
			GLenum RGBformat;
			switch (ncomponents)
			{
				case 1:
				RGBformat = GL_RED;
					break;
				
				case 3:
				RGBformat = GL_RGB;
					break;
				
				case 4:
				RGBformat = GL_RGBA;
					break;
			}

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, RGBformat, width, height, 0, RGBformat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			AE_CORE_ERROR("Texture failed to load at path given: {0}", path);
			stbi_image_free(data);
		}

		return textureID;
	}
}
