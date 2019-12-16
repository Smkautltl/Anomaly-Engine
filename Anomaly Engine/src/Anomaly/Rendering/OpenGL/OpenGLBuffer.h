#pragma once

#include <glm/vec3.hpp>
#include "../Primatives/Buffer.h"

namespace Anomaly
{
	struct Vertex;

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(Vertex vertices[], uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_BufferLayout = layout; };
		virtual const BufferLayout& GetLayout() const override { return m_BufferLayout; };

	private:
		uint32_t m_RendererID;
		BufferLayout m_BufferLayout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetCount() const override {return m_Count;};
		
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
		
	};
}