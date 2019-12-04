#pragma once

#include "RenderRequest.h"
#include "Primatives/Camera.h"
#include "Primatives/Shader.h"

namespace Anomaly
{
	class Renderer
	{
	public:
		static void BeginScene(PerspecCamera& camera);
		static void EndScene();

		static void SetUniform(const std::shared_ptr<Shader>& shader, const std::string& name, float& value)			{ shader->SetUniformFloat(name, value); }
		static void SetUniform(const std::shared_ptr<Shader>& shader, const std::string& name, bool& value)				{ shader->SetUniformBool(name, value); }
		static void SetUniform(const std::shared_ptr<Shader>& shader, const std::string& name, const glm::mat4& value)	{ shader->SetUniformMatrix4(name, value); }
		
		static void Submission(const std::shared_ptr<VertexArray>& vertexarray, const std::shared_ptr<Shader>& shader);		
		
		inline static RendererAPI::API GetRendererAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjMatrix;
		};

		static SceneData* m_SceneData;
	};
	
}
