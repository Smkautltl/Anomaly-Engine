#include "aepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Anomaly
{
	static GLenum ShaderDataType_To_GLenum(ShaderDataType Type)
	{
		switch (Type)
		{
			case ShaderDataType::Vec:	return GL_FLOAT;
			case ShaderDataType::Vec2:	return GL_FLOAT;
			case ShaderDataType::Vec3:	return GL_FLOAT;
			case ShaderDataType::Vec4:	return GL_FLOAT;
			
			case ShaderDataType::Mat3:	return GL_FLOAT;
			case ShaderDataType::Mat4:	return GL_FLOAT;
			
			case ShaderDataType::Int: 	return GL_INT;
			case ShaderDataType::Int2:	return GL_INT;
			case ShaderDataType::Int3:	return GL_INT;
			case ShaderDataType::Int4:	return GL_INT;
			
			case ShaderDataType::Bool:	return GL_BOOL;
		}

		AE_CORE_ASSERT(false, "Unknown shader data type!")
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glEnable(GL_DEPTH_TEST);
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer)
	{
		AE_CORE_ASSERT(vertexbuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!")

		Bind();
		vertexbuffer->Bind();

		//Enables and fills the vertex array attributes
		uint32_t i = 0;
		const auto& layout = vertexbuffer->GetLayout();
		for (const auto& element : layout)
		{	
			glVertexAttribPointer(i, 
								  element.GetComponentCount(), 
								  ShaderDataType_To_GLenum(element.Type), 
								  element.Normalized ? GL_TRUE : GL_FALSE, 
								  layout.GetStride(), 
								  reinterpret_cast<const void*>(element.Offset)
								 );
			glEnableVertexAttribArray(i);
			i++;
		}

		m_VertexBuffers.push_back(vertexbuffer);
	}
	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer)
	{
		Bind();
		indexbuffer->Bind();

		m_IndexBuffers.push_back(indexbuffer);
	}
}
