#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Renderer/Texture.h"

namespace Engine
{

	/* SHADER DATA TYPE */

	enum class ShaderDataType
	{
		None = 0,
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Bool

	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::None:		return 0;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Bool:		return 1;
		}
		
		ENGINE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}


	/* BUFFER ELEMENT */

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized;
		
		BufferElement() = default;
		BufferElement(ShaderDataType type, std::string name, bool normalized=false)
			: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
		{}

		uint32_t GetComponentCount() const
		{
			switch (type)
			{
			case ShaderDataType::None:		return 0;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3;
			case ShaderDataType::Mat4:		return 4;
			case ShaderDataType::Bool:		return 1;
			}

			ENGINE_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;

		}

	};


	/* BUFFER LAYOUT */

	class BufferLayout
	{

	public:

		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		const std::vector<BufferElement>& GetElements() const { return m_BufferElements; }

		std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_BufferElements.end(); }

		uint32_t GetStride() const { return m_Stride; }

	private:

		std::vector<BufferElement> m_BufferElements;
		uint32_t m_Stride = 0;

	private:

		void CalculateOffsetsAndStride();

	};


	/* VERTEX BUFFER */

	class VertexBuffer
	{
	public:

		virtual ~VertexBuffer() = default;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);

	};


	/* INDEX BUFFER */

	class IndexBuffer
	{
	public:

		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);

		virtual uint32_t GetCount() const = 0;

	};

}