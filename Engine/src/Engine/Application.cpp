#include "engpch.h"

#include "Application.h"

#include "Engine/Input.h"
#include "Engine/event/EventDispatcher.h"
#include "Engine/renderer/Renderer.h"

namespace Engine {

	Application* Application::s_instance = nullptr;

	Application::Application() 
	{
		// initialize application and create window
		ENGINE_CORE_ASSERT(!s_instance, "Application already exists");
		s_instance = this;
		m_running = true;
		m_window = Scope<Window>(Window::Create());
		
		// create default imgui layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// register observer
		m_window->RegisterObserver(this);




		/* HACKING IN A TRIANGLE */

		// VAO
		m_VertexArray.reset(VertexArray::Create());

		
		// vertices
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		// VBO
		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		// indices
		uint32_t indices[3] =
		{
			0, 1, 2
		};

		// VIO
		Ref<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// shaders

		std::string vertShaderSrc = R"(
			#version 330 core
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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

		m_shader.reset(Shader::Create(fragShaderSrc, vertShaderSrc));


		/* HACKING IN A TRIANGLE */




	}

	Application::~Application() 
	{

	}

	void Application::Run() 
	{
		while (m_running)
		{

			/* HACKING IN A TRIANGLE */
			RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });

			Renderer::BeginScene();
			m_shader->Bind();
			Renderer::Submit(m_VertexArray);
			Renderer::EndScene();
			/* HACKING IN A TRIANGLE */


			// LAYER :: OnUpdate()
			for (Layer* layer : m_layerStack)
			{
				if (layer->enabled) 
				{
					layer->OnUpdate();
				}
			}

			// LAYER :: OnImGuiRender()
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();


			// WINDOW :: On Update()
			m_window->OnUpdate();

		}
	}

	void Application::OnEvent(Event& e)
	{
		//ENGINE_CORE_TRACE("An Event Occurred!");
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ENG_BIND_EVENT_FN(Application::OnWindowCloseEvent));

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
		{
			if (e.handled) 
			{
				break;
			}
			else
			{
				(*it)->OnEvent(e);
			}
		}

	}


	bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		ENGINE_CORE_TRACE("Window Close Event! goodbye!");
		m_running = false;
		return true;
	}


	// LAYER STACK
	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

}