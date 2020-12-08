#pragma once

#include "Engine/renderer/RendererAPI.h"

namespace Engine
{

	class OpenGLRendererAPI : public RendererAPI
	{

		virtual void Clear() override;
		virtual void Clear(const glm::vec4& color) override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};

}