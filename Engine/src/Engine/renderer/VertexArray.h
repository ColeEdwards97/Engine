#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Renderer/Buffer.h"

namespace Engine
{

	class VertexArray
	{

	public:

		virtual ~VertexArray() {}

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexArray* Create();

	};

}