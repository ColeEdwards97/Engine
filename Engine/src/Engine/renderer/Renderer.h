#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"

namespace Engine
{

	class Renderer
	{

	public:

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		
	private:

		struct SceneData
		{
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* s_SceneData;

	};

}