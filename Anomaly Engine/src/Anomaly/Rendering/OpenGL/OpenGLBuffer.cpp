#include "aepch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>


//VERTEX BUFFER---------------------------------
Anomaly::OpenGLVertexBuffer::OpenGLVertexBuffer(Vertex vertices[], uint32_t size)
{
	glCreateBuffers(1, &m_RendererID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
Anomaly::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &m_RendererID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
Anomaly::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void Anomaly::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}
void Anomaly::OpenGLVertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//INDEX BUFFER---------------------------------
Anomaly::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	:m_Count(count)
{
	glCreateBuffers(1, &m_RendererID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}
Anomaly::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}
void Anomaly::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}
void Anomaly::OpenGLIndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Anomaly::OpenGLFrameBuffer::OpenGLFrameBuffer()
{
	glGenFramebuffers(1, &m_FrameBuffer);
	Bind();
	glGenTextures(1, &m_TextureBuffer);
	glBindTexture(GL_TEXTURE_2D, m_TextureBuffer);
	glGenRenderbuffers(1, &m_RenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1600, 900, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureBuffer, 0);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1600, 900);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
		{
			AE_CORE_ERROR("FrameBuffer is not completed! - Incomplete Attachment");
		}
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
		{
			AE_CORE_ERROR("FrameBuffer is not completed! - Incomplete Draw Buffer");
		}
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)
		{
			AE_CORE_ERROR("FrameBuffer is not completed! - Incomplete Layer Targets");
		}
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
		{
			AE_CORE_ERROR("FrameBuffer is not completed! - Missing Attachment");
		}
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
		{
			AE_CORE_ERROR("FrameBuffer is not completed! - Incomplete Multisample");
		}
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
		{
			AE_CORE_ERROR("FrameBuffer is not completed! - Incomplete Read Buffer");
		}
	}
	UnBind();
}

Anomaly::OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
	glDeleteBuffers(1, &m_FrameBuffer);
}

void Anomaly::OpenGLFrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}
void Anomaly::OpenGLFrameBuffer::UnBind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Anomaly::OpenGLFrameBuffer::UpdateBuffer(unsigned texturebuffer)
{
	glBindTexture(GL_TEXTURE_2D, m_TextureBuffer);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureBuffer, 0);

	glGenRenderbuffers(1, &m_RenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);
}
unsigned Anomaly::OpenGLFrameBuffer::ReturnFrameBuffer(float Width, float Height)
{
	const int iWidth = static_cast<int>(Width);
	const int iHeight = static_cast<int>(Height);
	
	glViewport(0, 0, iWidth, iHeight);
	
	Bind();
	glBindTexture(GL_TEXTURE_2D, m_TextureBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureBuffer, 0);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, iWidth, iHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);
	UnBind();
	
	return m_FrameBuffer;
}
