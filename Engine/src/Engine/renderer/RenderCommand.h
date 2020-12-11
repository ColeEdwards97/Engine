#pragma once

#include "RendererAPI.h"

namespace Engine
{

	class RenderCommand
	{

	public:

		inline static void Clear() { s_RendererAPI->Clear(); }
		inline static void Clear(const glm::vec4& color) { s_RendererAPI->Clear(color); }
		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewport(x, y, width, height); }

	private:

		static RendererAPI* s_RendererAPI;

	};

}