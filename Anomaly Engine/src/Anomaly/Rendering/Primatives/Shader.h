#pragma once

#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Anomaly
{
	class Shader
	{
	public:
		Shader(const char* VertexSrcPath,const char* FragmentSrcPath, const char* geometryPath = nullptr);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void GenerateTextures(const std::vector<char*> SrcFileName);
		void BindTexture(unsigned int id);
		void BindAllTextures();
		
		void SetUniformMatrix4(const std::string& name, const glm::mat4& matrix) const;
		void SetUniformBool(const std::string& name, bool value) const;
		void SetUniformInt(const std::string& name, int value) const;
		void SetUniformFloat(const std::string& name, float value) const;
		void SetUniformVec3(const std::string& name, glm::vec3 value) const;

		void SetActiveTexture(int num);
	private:
		void ReadInShaders(const char* VertexSrcFileName,const char* FragmentSrcFileName, const char*
			                   geometrySrcFileName = nullptr);
		void CheckComplied(unsigned int shader, std::string type);
		
	private:
		unsigned int m_RendererID;
		std::string VertexSrc;
		std::string FragmentSrc;
		std::string GeomSrc;
		std::vector<unsigned int> m_textures;
		const char* vPath;
		const char* fPath;
		const char* gPath;
		
	};
}
