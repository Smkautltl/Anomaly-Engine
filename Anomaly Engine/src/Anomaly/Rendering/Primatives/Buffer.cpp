#include "aepch.h"
#include "Buffer.h"

#include "../Renderer.h"
#include "../OpenGL/OpenGLBuffer.h"

namespace Anomaly
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::None:
				AE_CORE_ASSERT(false, "Renderer API set to None!");
				return nullptr;
			
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
				break;
		}

		AE_CORE_ASSERT(false, "Renderer API has not been set!");
		return nullptr;
	}
	VertexBuffer* VertexBuffer::Create(Vertex vertices[], uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::None:
				AE_CORE_ASSERT(false, "Renderer API set to None!");
				return nullptr;
			
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
				break;
		}

		AE_CORE_ASSERT(false, "Renderer API has not been set!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::None:
				AE_CORE_ASSERT(false, "Renderer API set to None!");
				return nullptr;
			
			case RendererAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, size);
				break;
		}

		AE_CORE_ASSERT(false, "Renderer API has not been set!");
		return nullptr;
	}

	FrameBuffer* FrameBuffer::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::None:
				AE_CORE_ASSERT(false, "Renderer API set to None!");
				return nullptr;
			
			case RendererAPI::API::OpenGL:
				return new OpenGLFrameBuffer();
				break;
		}
	
		AE_CORE_ASSERT(false, "Renderer API has not been set!");
		return nullptr;
	}
}
