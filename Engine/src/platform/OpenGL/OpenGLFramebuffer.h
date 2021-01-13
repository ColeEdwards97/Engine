#pragma once

#include "Engine/Renderer/Framebuffer.h"

namespace Engine
{

	class OpenGLFramebuffer : public Framebuffer
	{

	public:

		OpenGLFramebuffer(const FramebufferSpecification& specification);
		virtual ~OpenGLFramebuffer();

		virtual void Invalidate() override;

		virtual void Bind() override;
		virtual void BindRead() override;
		virtual void BindWrite() override;
		virtual void Unbind() override;
		virtual void UnbindRead() override;
		virtual void UnbindWrite() override;

		virtual void Attach(FramebufferAttachmentType type) override;
		virtual uint32_t GetAttachment(uint32_t index) override;
		virtual void SetActiveAttachment(uint32_t index) override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Blit() override;


		// disable depth
		virtual void DepthTest(bool test) override;


	private:

		FramebufferSpecification m_Specification;
		uint32_t m_BufferID = 0;
		uint32_t m_ColorAttachment0 = 0;
		uint32_t m_ColorAttachment1 = 0;
		uint32_t m_ColorAttachment2 = 0;
		uint32_t m_DepthAttachment = 0;

	};

}