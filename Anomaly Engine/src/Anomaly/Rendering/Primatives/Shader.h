#pragma once

#include <string>
#include <fstream>

#include <glm/glm.hpp>

namespace Anomaly
{
	class Shader
	{
	public:
		Shader(const char* VertexSrcPath,const char* FragmentSrcPath);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void GenerateTextures();
		void BindTextures();
		
		void SetUniformMatrix4(const std::string& name, const glm::mat4& matrix);
		void SetUniformBool(const std::string& name, bool value);
		void SetUniformInt(const std::string& name, int value);
		void SetUniformFloat(const std::string& name, float value);

	private:
		void ReadInShaders(const char* VertexSrcFileName,const char* FragmentSrcFileName);
		
	private:
		uint32_t m_RendererID;
		std::string VertexSrc;
		std::string FragmentSrc;
		unsigned int texture0;
	};
}
