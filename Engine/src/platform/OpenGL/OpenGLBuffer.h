#pragma once

#include "Engine/renderer/Buffer.h"

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

}