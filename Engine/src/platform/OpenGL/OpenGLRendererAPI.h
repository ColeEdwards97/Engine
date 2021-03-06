#pragma once

#include "Engine/Renderer/RendererAPI.h"

namespace Engine
{

	class OpenGLRendererAPI : public RendererAPI
	{

		virtual void Clear() override;
		virtual void Clear(const glm::vec4& color) override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

	};

}