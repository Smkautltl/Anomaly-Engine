#include "aepch.h"
#include "VertexArray.h"

#include "../OpenGL/OpenGLVertexArray.h"

namespace Anomaly
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::None:
				AE_CORE_ASSERT(false, "Renderer API set to None!");
				return nullptr;
			
			case RendererAPI::OpenGL:
				return new OpenGLVertexArray();
				break;
		}

		AE_CORE_ASSERT(false, "Renderer API has not been set!");
		return nullptr;
	}
}