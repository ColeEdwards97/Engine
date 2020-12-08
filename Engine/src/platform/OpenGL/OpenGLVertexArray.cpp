#include "engpch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Engine
{

	/* SHADER DATA TYPE */
	static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Engine::ShaderDataType::None:		return GL_NONE;
		case Engine::ShaderDataType::Int:		return GL_INT;
		case Engine::ShaderDataType::Int2:		return GL_INT;
		case Engine::ShaderDataType::Int3:		return GL_INT;
		case Engine::ShaderDataType::Int4:		return GL_INT;
		case Engine::ShaderDataType::Float:		return GL_FLOAT;
		case Engine::ShaderDataType::Float2:	return GL_FLOAT;
		case Engine::ShaderDataType::Float3:	return GL_FLOAT;
		case Engine::ShaderDataType::Float4:	return GL_FLOAT;
		case Engine::ShaderDataType::Mat3:		return GL_FLOAT_MAT3;
		case Engine::ShaderDataType::Mat4:		return GL_FLOAT_MAT4;
		case Engine::ShaderDataType::Bool:		return GL_BOOL;
		}

		ENGINE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return GL_NONE;
	}



	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_ArrayID);
	}


	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ArrayID);
	}
	

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}


	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		ENGINE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");

		glBindVertexArray(m_ArrayID);
		vertexBuffer->Bind();

		uint32_t idx = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			// vertex attrib arrays
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(
				idx,
				element.GetComponentCount(),
				ShaderDataTypeToGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.offset
			);
			idx++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}
	
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_ArrayID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}