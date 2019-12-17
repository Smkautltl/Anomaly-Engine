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

		void GenerateTextures();
		void BindTextures(unsigned int id);
		
		void SetUniformMatrix4(const std::string& name, const glm::mat4& matrix);
		void SetUniformBool(const std::string& name, bool value);
		void SetUniformInt(const std::string& name, int value);
		void SetUniformFloat(const std::string& name, float value);
		void SetUniformVec3(const std::string& name, glm::vec3 value);

		void SetActiveTexture(int num);
	private:
		void ReadInShaders(const char* VertexSrcFileName,const char* FragmentSrcFileName, const char* geometryPath = nullptr);
		void CheckComplied(unsigned int shader, std::string type);
		
	private:
		unsigned int m_RendererID;
		std::string VertexSrc;
		std::string FragmentSrc;
		std::string GeomSrc;
		unsigned int texture0{};
		unsigned int texture1{};
	};
}
