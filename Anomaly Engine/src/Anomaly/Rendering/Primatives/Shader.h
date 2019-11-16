#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Anomaly
{
	class Shader
	{
	public:
		Shader(const std::string& VertexSrc,const std::string& FragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void AddUniformMatrix4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;
	};
}
