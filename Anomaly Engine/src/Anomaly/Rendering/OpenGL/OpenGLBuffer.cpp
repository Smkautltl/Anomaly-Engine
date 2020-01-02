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

//Anomaly::OpenGLFrameBuffer::OpenGLFrameBuffer(unsigned int textureBuffer)
//{
//	glGenFramebuffers(1, &m_FrameBuffer);
//	glGenRenderbuffers(1, &m_RenderBuffer);
//	Bind();
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280.f, 720.f);
//	UpdateBuffer(textureBuffer);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);
//	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		AE_CORE_ERROR("Frame buffer is not complete");
//	UnBind();
//}
//
//void Anomaly::OpenGLFrameBuffer::Bind() const
//{
//	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
//	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
//}
//
//void Anomaly::OpenGLFrameBuffer::UnBind() const
//{
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//}
//
//void Anomaly::OpenGLFrameBuffer::UpdateBuffer(unsigned texturebuffer)
//{
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texturebuffer, 0);
//}
