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

	glGenTextures(1, &m_textureBuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280.f, 720.f, 0, GL_RGB, GL_UNSIGNED_INT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureBuffer, 0);
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
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texturebuffer, 0);
}
unsigned Anomaly::OpenGLFrameBuffer::ReturnFrameBuffer(float x, float y, float Width, float Height)
{
	glViewport(0, 0, Width, Height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_INT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureBuffer, 0);
	return m_textureBuffer;
}
