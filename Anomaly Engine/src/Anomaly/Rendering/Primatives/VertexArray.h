#pragma once

#include <memory>

#include "Buffer.h"

namespace Anomaly
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;;

		static VertexArray* Create();
		
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) = 0;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::vector<std::shared_ptr<IndexBuffer>>& GetIndexBuffers() const = 0;
		
	};
}