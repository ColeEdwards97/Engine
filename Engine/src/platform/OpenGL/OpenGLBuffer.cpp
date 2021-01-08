#include "engpch.h"

#include "OpenGLBuffer.h"

namespace Engine
{

	/* OPENGL VERTEX BUFFER */
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}
	

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	/* OPENGL INDEX BUFFER */
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	/* OPENGL FRAME BUFFER */
	OpenGLFrameBuffer::OpenGLFrameBuffer()
	{
		glCreateFramebuffers(1, &m_BufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_BufferID);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
	}

	void OpenGLFrameBuffer::BindRead() const
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_BufferID);
	}

	void OpenGLFrameBuffer::BindWrite() const
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_BufferID);
	}

	void OpenGLFrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::UnbindRead() const
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::UnbindWrite() const
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Attach(Texture2D& texture, uint32_t attachment) const
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture.GetTextureID(), 0);
	}


	/* OPENGL G BUFFER */
	OpenGLGBuffer::OpenGLGBuffer(int width, int height)
	{
		// bind the Framebuffer
		m_FBO.Bind();

		// create textures
		glGenTextures(NUM_TEXTURES, m_Textures);
		glBindTextures(m_Textures[0], NUM_TEXTURES, m_Textures);
		for (int i = 0; i < NUM_TEXTURES; i++)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_Textures[i], 0);
		}
		
		// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
		GLuint attachments[NUM_TEXTURES] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(NUM_TEXTURES, attachments);

		// create depth texture
		glGenRenderbuffers(1, &m_DepthTexture);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthTexture);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthTexture);
		
		// finally check if Framebuffer is complete
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		ENGINE_CORE_ASSERT((status), "Framebuffer is not complete!");

		// unbind the Framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	OpenGLGBuffer::~OpenGLGBuffer()
	{
		glDeleteTextures(NUM_TEXTURES, m_Textures);
		glDeleteTextures(1, &m_DepthTexture);
	}

	

}