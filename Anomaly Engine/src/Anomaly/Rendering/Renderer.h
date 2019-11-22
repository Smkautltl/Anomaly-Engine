#pragma once

#include "RenderRequest.h"
#include "Primatives/Camera.h"
#include "Primatives/Shader.h"

namespace Anomaly
{
	class Renderer
	{
	public:
		static void BeginScene(OrthoCamera& camera);
		static void EndScene();

		static void Submission(const std::shared_ptr<VertexArray>& vertexarray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));		
		
		inline static RendererAPI::API GetRendererAPI() {return RendererAPI::GetAPI();}

	private:
		struct SceneData
		{
			glm::mat4 ViewProjMatrix;
		};

		static SceneData* m_SceneData;
	};
	
}
