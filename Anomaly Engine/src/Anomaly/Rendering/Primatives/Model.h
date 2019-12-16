#pragma once
#include "Shader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "assimp/scene.h"

namespace Anomaly
{
	class Model
	{
	public:
		Model(const char* path) { loadModel(path); }

		void Draw(std::shared_ptr<Shader> shader);

	private:
		void loadModel(std::string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
		unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

	private:
		std::vector<Mesh> m_meshes;
		std::string m_directory;
		std::vector<Texture> m_TexturesLoaded;
	};
	
}
