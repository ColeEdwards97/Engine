#pragma once

#include <Engine.h>

#include "imgui/imgui.h"

class TestLayer : public Engine::Layer
{
public:

	TestLayer()
		//: Layer("Test Layer"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f), m_CameraPosition(glm::vec3(0.0f)), m_CameraRotation(glm::vec3(0.0f))		// orthographic cam
		: Layer("Test Layer"), m_CameraController(45.0f, (1024.0f / 720.0f)), m_TriangleTransform()		// perspective cam
	{

		/* HACKING IN A TRIANGLE */

		// VAO
		m_VertexArray.reset(Engine::VertexArray::Create());


		// vertices
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};


		// VBO
		Engine::Ref<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ Engine::ShaderDataType::Float3, "a_Position" },
			{ Engine::ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		// indices
		uint32_t indices[3] =
		{
			0, 1, 2
		};

		// VIO
		Engine::Ref<Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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

		m_Shader.reset(Engine::Shader::Create(fragShaderSrc, vertShaderSrc));

		// transform setup
		m_TriangleTransform.SetLocation(glm::vec3(0.0f, 0.0f, 0.0f));

		/* HACKING IN A TRIANGLE */


	}

	void OnUpdate(Engine::TimeStep ts) override
	{

		// CAMERA CONTROLLER UPDATE
		m_CameraController.OnUpdate(ts);

		// TRIANGLE TRANSFORM
		//m_TriangleTransform.Rotate(ts * 30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		//m_TriangleTransform.SetScale((glm::sin(totalTime) * 0.4f + 0.5f) * glm::vec3(1.0f));
		//m_TriangleTransform.Scale(1.0f, glm::vec3(1.0f));
		totalTime += ts;

		/* HACKING IN A TRIANGLE */
		Engine::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });
		Engine::Renderer::BeginScene(m_CameraController.GetCamera());
		Engine::Renderer::Submit(m_Shader, m_VertexArray, m_TriangleTransform.GetTransformMatrix());
		Engine::Renderer::EndScene();
		/* HACKING IN A TRIANGLE */

	}

	void OnEvent(Engine::Event& e) override
	{
		//ENGINE_TRACE("An Event Occurred!");

		// CAMERA CONTROLLER EVENT
		m_CameraController.OnEvent(e);
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

	Engine::PerspectiveCameraController m_CameraController;
	//Engine::OrthographicCamera m_Camera;

	Engine::Transform m_TriangleTransform;
	float totalTime = 0.0f;

	/* hacking in triangle */


};