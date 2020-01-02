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

	void OpenGLRendererAPI::DrawCall(const std::shared_ptr<VertexArray>& vertexarray, const std::shared_ptr<Shader>& shader)
	{
		vertexarray->Bind();
		glDrawElements(GL_TRIANGLES, vertexarray->GetIndexBuffers()[0]->GetCount(), GL_UNSIGNED_INT, 0);
		vertexarray->UnBind();
		glActiveTexture(GL_TEXTURE0);
		
	}
}
