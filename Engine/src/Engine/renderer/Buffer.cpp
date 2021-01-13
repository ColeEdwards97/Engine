#include "engpch.h"

#include "Buffer.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{
	
	/* VERTEX BUFFER */

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	ENGINE_CORE_ASSERT(false, "None RendererAPI is not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}


	/* INDEX BUFFER */
	
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	ENGINE_CORE_ASSERT(false, "None RendererAPI is not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLIndexBuffer>(indices, size);
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