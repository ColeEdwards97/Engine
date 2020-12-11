#include "engpch.h"

#include "Renderer.h"

namespace Engine
{

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(Camera& camera)
	{
		s_SceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}


	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->viewProjectionMatrix);
		shader->SetMat4("u_TransformMatrix", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}