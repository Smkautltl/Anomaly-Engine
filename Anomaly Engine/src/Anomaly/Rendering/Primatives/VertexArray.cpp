#include "aepch.h"
#include "VertexArray.h"

#include "Anomaly/Rendering/Renderer.h"
#include "../OpenGL/OpenGLVertexArray.h"

namespace Anomaly
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::None:
				AE_CORE_ASSERT(false, "RendererAPI has not been selected!");
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return new OpenGLVertexArray();
		}

		AE_CORE_ASSERT(false, "Renderer API has not been set!");
		return nullptr;
	}
}
