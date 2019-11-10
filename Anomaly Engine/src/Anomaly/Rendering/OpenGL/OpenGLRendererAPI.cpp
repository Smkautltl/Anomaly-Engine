#include "aepch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Anomaly
{
	void OpenGLRendererAPI::SetClearColour(const glm::vec4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);			
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawCall(const std::shared_ptr<VertexArray>& vertexarray)
	{
		for (auto IB : vertexarray->GetIndexBuffers())
		{
			glDrawElements(GL_TRIANGLES, IB->GetCount(), GL_UNSIGNED_INT, nullptr);	
		}	
	}
}
