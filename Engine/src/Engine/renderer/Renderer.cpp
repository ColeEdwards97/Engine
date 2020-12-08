#include "engpch.h"

#include "Renderer.h"

namespace Engine
{

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}


	void Renderer::Submit(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}