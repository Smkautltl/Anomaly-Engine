#include "aepch.h"
#include "Renderer.h"

namespace Anomaly
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submission(const std::shared_ptr<VertexArray>& vertexarray)
	{
		vertexarray->Bind();
		RenderRequest::DrawCall(vertexarray);
	}
}
