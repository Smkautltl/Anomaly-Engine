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

		void AddUniformMatrix4(const std::string& name, const glm::mat4& matrix);

	private:
		void ReadInShaders(const char* VertexSrcFileName,const char* FragmentSrcFileName);
		
	private:
		uint32_t m_RendererID;
		std::string VertexSrc;
		std::string FragmentSrc;
	};
}
