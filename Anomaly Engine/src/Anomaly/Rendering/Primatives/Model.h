#pragma once
#include "Shader.h"
#include "Mesh.h"

#include "Importer.hpp"
#include <scene.h>
#include <postprocess.h>

namespace Anomaly
{
	class Model
	{
	public:
		Model(std::string path, bool gamma = false)
			:m_GammaCorrection(gamma)
		{
			std::string AppPath = __argv[0];	
			AppPath.replace(AppPath.end() - 11, AppPath.end(), path);
			const char* Path = AppPath.c_str();
			
			loadModel(Path);
		}

		virtual void Draw(std::shared_ptr<Shader> shader);

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
		bool m_GammaCorrection;
	};

	class InstancedModel : public Model
	{
		virtual void Draw(std::shared_ptr<Shader> shader) override;

	private:
		int NoOfInstances;
		std::vector<glm::vec3> InstancesPos;
	};
}
