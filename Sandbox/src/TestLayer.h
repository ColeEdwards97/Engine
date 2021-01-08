#pragma once

#include <Engine.h>
#include <imgui/imgui.h>

#include "TestEntity.h"

class TestLayer : public Engine::Layer
{
public:

	TestLayer()
		: Layer("Test Layer"), m_CubeTransform()
	{

		/* HACKING IN A TRIANGLE */

		// VAO
		m_VertexArray.reset(Engine::VertexArray::Create());


		// vertices

		float vertices[8 * 7] =
		{
			// front
			-1.0, -1.0,  1.0, 1.0f, 0.0f, 0.0f, 1.0f,
			 1.0, -1.0,  1.0, 1.0f, 1.0f, 0.0f, 1.0f,
			 1.0,  1.0,  1.0, 0.0f, 1.0f, 1.0f, 1.0f,
			-1.0,  1.0,  1.0, 0.0f, 0.0f, 1.0f, 1.0f,
			// back
			-1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 1.0f,
			 1.0, -1.0, -1.0, 1.0f, 1.0f, 0.0f, 1.0f,
			 1.0,  1.0, -1.0, 0.0f, 1.0f, 1.0f, 1.0f,
			-1.0,  1.0, -1.0, 0.0f, 0.0f, 1.0f, 1.0f,
		};


		// VBO
		Engine::Ref<Engine::VertexBuffer> vertexBuffer = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{ Engine::ShaderDataType::Float3, "a_Position" },
			{ Engine::ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		// indices

		uint32_t indices[36] =
		{
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3
		};

		// VIO
		Engine::Ref<Engine::IndexBuffer> indexBuffer = Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// shaders

		std::string vertShaderSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_TransformMatrix;
			
			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_TransformMatrix * vec4(a_Position, 1.0);
			}
		)";

		std::string fragShaderSrc = R"(
			#version 330 core
			layout(location=0) out vec4 color;
			in vec4 v_Color;
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader = Engine::Shader::Create(fragShaderSrc, vertShaderSrc);

		// transform setup
		m_CubeTransform.SetLocation(glm::vec3(0.0f, 0.0f, 0.0f));

		/* HACKING IN A TRIANGLE */

		

		/* ENTITY TEST */
		
		Engine::ECS::Init();

		// Create Controller System
		Engine::SystemManager::Get().CreateSystem<Engine::ControllerSystem>();

		// Create Camera Entity
		m_Camera = Engine::EntityManager::Get().CreateEntity<Engine::Camera>();
		// Create Camera Controller
		Engine::CameraController* controller = new Engine::CameraController(m_Camera);
		// Create Controller Component
		m_Camera->AddComponent<Engine::ControllerComponent>();
		Engine::Ref<Engine::ControllerComponent> controller_comp = m_Camera->GetComponent<Engine::ControllerComponent>();
		// Attach Camera Controller to Controller Component
		controller_comp->SetController(controller);


		/* ENTITY TEST */

	}

	void OnUpdate(Engine::TimeStep ts) override
	{

		/* CAMERA SYSTEM TEST */
		Engine::SystemManager::Get().GetSystem<Engine::ControllerSystem>()->OnUpdate(ts);
		/* CAMERA SYSTEM TEST */

		/* HACKING IN A TRIANGLE */
		Engine::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });
		Engine::Renderer::BeginScene(m_Camera);
		Engine::Renderer::Submit(m_Shader, m_VertexArray, m_CubeTransform.GetTransformMatrix());
		Engine::Renderer::EndScene();
		/* HACKING IN A TRIANGLE */

	}

	void OnEvent(Engine::Event& e) override
	{
		// CAMERA CONTROLLER EVENT
		Engine::SystemManager::Get().GetSystem<Engine::ControllerSystem>()->OnEvent(e);

	}
	
	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world!");
		ImGui::End();
	}


private:

	/* hacking in triangle */
	Engine::Ref<Engine::Shader> m_Shader;
	Engine::Ref<Engine::VertexArray> m_VertexArray;

	Engine::Transform m_CubeTransform;
	float totalTime = 0.0f;

	Engine::Ref<Engine::Camera> m_Camera;

	/* hacking in triangle */


};