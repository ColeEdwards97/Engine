#pragma once

#include "Texture.h"

namespace Engine
{

	class RenderTarget
	{
	public:
		virtual ~RenderTarget() = default;

	};


	class FramebufferLayout
	{
	public:

		// TODO: specify what kind of information is needed so framebuffer implementations can use the best layouts
		// similar to BufferLayout

	};


	struct FramebufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		uint32_t Samples = 1;
		uint32_t MaxSize = 8192;
		bool SwapchainTarget = false;
	};

	class Framebuffer
	{
	public:

		virtual ~Framebuffer() = default;

		virtual void Invalidate() = 0;

		virtual void Bind() = 0;
		virtual void BindRead() = 0;
		virtual void BindWrite() = 0;
		virtual void Unbind() = 0;
		virtual void UnbindRead() = 0;
		virtual void UnbindWrite() = 0;
		
		virtual uint32_t GetAttachment(uint32_t index) = 0;
		virtual void SetActiveAttachment(uint32_t index) = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& specification);

	};

}