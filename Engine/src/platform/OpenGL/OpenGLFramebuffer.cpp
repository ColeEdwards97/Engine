#include "engpch.h"

#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Engine
{

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specification)
		: m_Specification(specification)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		// delete framebuffer
		GL_CALL(glDeleteFramebuffers(1, &m_BufferID));

		// delete textures
		GL_CALL(glDeleteTextures(1, &m_ColorAttachment0));
		GL_CALL(glDeleteTextures(1, &m_ColorAttachment1));
		GL_CALL(glDeleteTextures(1, &m_ColorAttachment2));
		GL_CALL(glDeleteTextures(1, &m_DepthAttachment));
	}

	void OpenGLFramebuffer::Invalidate()
	{

		if (m_BufferID)
		{
			// delete framebuffer
			GL_CALL(glDeleteFramebuffers(1, &m_BufferID));
			// delete textures
			GL_CALL(glDeleteTextures(1, &m_ColorAttachment0));
			GL_CALL(glDeleteTextures(1, &m_ColorAttachment1));
			GL_CALL(glDeleteTextures(1, &m_ColorAttachment2));
			GL_CALL(glDeleteTextures(1, &m_DepthAttachment));
			GL_CALL(glDeleteTextures(1, &m_DepthAttachment));
		}

		// create framebuffer
		GL_CALL(glCreateFramebuffers(1, &m_BufferID));
		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID));

		// create textures
		GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment0));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ColorAttachment0));
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GL_CALL(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_ColorAttachment0, 0));

		GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment1));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ColorAttachment1));
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GL_CALL(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, m_ColorAttachment1, 0));

		GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment2));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ColorAttachment2));
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GL_CALL(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, m_ColorAttachment2, 0));
		
		// create depth texture
		GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_DepthAttachment));
		GL_CALL(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height));
		GL_CALL(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, m_DepthAttachment, 0));
		
		GLenum drawBuffers[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		GL_CALL(glDrawBuffers(3, drawBuffers));

		// check framebuffer status
		ENGINE_CORE_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Framebuffer is incomplete");

		// unbind framebuffer
		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void OpenGLFramebuffer::Bind()
	{
		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID));
		GL_CALL(glViewport(0, 0, m_Specification.Width, m_Specification.Height));
	}

	void OpenGLFramebuffer::BindRead()
	{
		GL_CALL(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_BufferID));
		GL_CALL(glViewport(0, 0, m_Specification.Width, m_Specification.Height));
	}

	void OpenGLFramebuffer::BindWrite()
	{
		GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_BufferID));
		GL_CALL(glViewport(0, 0, m_Specification.Width, m_Specification.Height));
	}

	void OpenGLFramebuffer::Unbind()
	{
		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void OpenGLFramebuffer::UnbindRead()
	{
		GL_CALL(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
	}

	void OpenGLFramebuffer::UnbindWrite()
	{
		GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
	}

	void OpenGLFramebuffer::Attach(FramebufferAttachmentType type)
	{
		
	}

	void OpenGLFramebuffer::SetActiveAttachment(uint32_t index)
	{
		GL_CALL(glActiveTexture(GL_TEXTURE0 + index));
		uint32_t id = 0;
		switch (index)
		{
		case 0: id = m_ColorAttachment0; break;
		case 1: id = m_ColorAttachment1; break;
		case 2: id = m_ColorAttachment2; break;
		default:
			break;
		}
		GL_CALL(glBindTexture(GL_TEXTURE_2D, id));
	}

	uint32_t OpenGLFramebuffer::GetAttachment(uint32_t index)
	{
		uint32_t id = 0;
		switch (index)
		{
		case 0: id = m_ColorAttachment0; break;
		case 1: id = m_ColorAttachment1; break;
		case 2: id = m_ColorAttachment2; break;
		default:
			break;
		}
		return id;
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > m_Specification.MaxSize || height > m_Specification.MaxSize)
		{
			ENGINE_CORE_WARN("Attempted to resize Framebuffer to unsupported value: {0}x{1}", width, height);
			return;
		}
		m_Specification.Width = width;
		m_Specification.Height = height;
	}

	void OpenGLFramebuffer::Blit()
	{
		GL_CALL(glBlitFramebuffer(0, 0, m_Specification.Width, m_Specification.Height, 0, 0, m_Specification.Width, m_Specification.Height, GL_COLOR_BUFFER_BIT, GL_NEAREST));
	}


	void OpenGLFramebuffer::DepthTest(bool test)
	{
		if (test)
		{
			GL_CALL(glEnable(GL_DEPTH_TEST));
		}
		else
		{
			GL_CALL(glDisable(GL_DEPTH_TEST));
		}
	}

}