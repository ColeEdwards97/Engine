#pragma once

#include "Engine/Renderer/Buffer.h"

#include <glad/glad.h>

namespace Engine
{

	/* OPENGL VERTEX BUFFER */

	class OpenGLVertexBuffer : public VertexBuffer
	{

	public:

		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:

		uint32_t m_BufferID;
		BufferLayout m_Layout;

	};


	/* OPENGL INDEX BUFFER */

	class OpenGLIndexBuffer : public IndexBuffer
	{

	public:
	
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }
		
	private:

		uint32_t m_BufferID;
		uint32_t m_Count;

	};


	/* OPENGL FRAME BUFFER */

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer();
		virtual ~OpenGLFrameBuffer();

		virtual void Bind() const override;
		virtual void BindRead() const override;
		virtual void BindWrite() const override;
		virtual void Unbind() const override;
		virtual void UnbindRead() const override;
		virtual void UnbindWrite() const override;
		
		virtual void Attach(Texture2D& texture, uint32_t attachment) const override;

	private:
		uint32_t m_BufferID;
	};


	/* OPENGL G BUFFER */

	class OpenGLGBuffer : public GBuffer
	{
	public:
		OpenGLGBuffer(int width, int height);
		virtual ~OpenGLGBuffer();

		virtual FrameBuffer& GetFrameBuffer() { return m_FBO; }

	private:
		OpenGLFrameBuffer m_FBO;
		GLuint m_Textures[NUM_TEXTURES];
		GLuint m_DepthTexture;
	};

}