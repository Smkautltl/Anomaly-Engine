#include "aepch.h"
#include "Renderer.h"

namespace Anomaly
{

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	
	void Renderer::BeginScene(OrthoCamera& camera)
	{
		m_SceneData->ViewProjMatrix = camera.GetViewProjMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submission(const std::shared_ptr<VertexArray>& vertexarray, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->AddUniformMatrix4("u_ViewProjMatrix", m_SceneData->ViewProjMatrix);
		vertexarray->Bind();
		RenderRequest::DrawCall(vertexarray);
	}
}
