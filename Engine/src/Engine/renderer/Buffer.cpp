#include "engpch.h"

#include "Buffer.h"
#include "Renderer.h"
#include "platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{
	
	/* VERTEX BUFFER */

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}


	/* INDEX BUFFER */
	
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}
	
		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}


	/* BUFFER LAYOUT */

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_BufferElements(elements)
	{
		CalculateOffsetsAndStride();
	}


	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_BufferElements)
		{
			element.offset = offset;
			offset += element.size;
			m_Stride += element.size;
		}
	}

}