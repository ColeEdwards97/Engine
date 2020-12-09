#pragma once

#include "Engine.h"

#include "imgui/imgui.h"

class TestLayer : public Engine::Layer
{
public:

	TestLayer()
		: Layer("Test Layer"), m_Camera(45.0f, (1024.0f / 720.0f), 0.1f, 100.0f), m_CameraPosition(glm::vec3(0.0f))
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
			
			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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


		// camera setup
		m_Camera.SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
		m_Camera.LookAt(glm::vec3(0.0f, 0.0f, 0.0f));


		/* HACKING IN A TRIANGLE */


	}

	void OnUpdate() override
	{

		if (Engine::Input::IsKeyPressed(INPUT_KEY_W))
		{
			m_CameraPosition.x += 0.1f;
		}
		if (Engine::Input::IsKeyPressed(INPUT_KEY_A))
		{
			m_CameraPosition.z += -0.1f;
		}
		if (Engine::Input::IsKeyPressed(INPUT_KEY_S))
		{
			m_CameraPosition.x += -0.1f;
		}
		if (Engine::Input::IsKeyPressed(INPUT_KEY_D))
		{
			m_CameraPosition.z += 0.1f;
		}


		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.LookAt(glm::vec3(0.0f));

		/* HACKING IN A TRIANGLE */
		Engine::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });
		Engine::Renderer::BeginScene(m_Camera);
		Engine::Renderer::Submit(m_Shader, m_VertexArray);
		Engine::Renderer::EndScene();
		/* HACKING IN A TRIANGLE */

	}

	void OnEvent(Engine::Event& e) override
	{
		//ENGINE_TRACE("An Event Occurred!");
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

	Engine::PerspectiveCamera m_Camera;
	//Engine::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	/* hacking in triangle */


};