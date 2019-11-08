#pragma once

#include "../Primatives/VertexArray.h"

namespace Anomaly
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		
		virtual ~OpenGLVertexArray();
		
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) override;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };
		virtual const std::vector<std::shared_ptr<IndexBuffer>>& GetIndexBuffers() const override { return m_IndexBuffers; };
		
	private:
		uint32_t m_RendererID;
		
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::vector<std::shared_ptr<IndexBuffer>> m_IndexBuffers;
	};
}