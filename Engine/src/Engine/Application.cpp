#include "engpch.h"

#include "Application.h"

#include "glad/glad.h"

#include "Input.h"

#include "event/EventDispatcher.h"

namespace Engine {

	Application* Application::s_instance = nullptr;

	Application::Application() 
	{
		// initialize application and create window
		ENGINE_CORE_ASSERT(!s_instance, "Application already exists");
		s_instance = this;
		m_running = true;
		m_window = std::unique_ptr<Window>(Window::Create());
		
		// create default imgui layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// register observer
		m_window->RegisterObserver(this);




		/* HACKING IN A TRIANGLE */
		
		// VAO
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// VBO
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// vertices
		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		// buffer data
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// vertex attrib arrays
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);


		// VIO
		glGenBuffers(1, &VIO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VIO);

		// indices
		unsigned int indices[3] =
		{
			0, 1, 2
		};

		// buffer data
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// shader
		std::string fragShaderSrc = R"(
			#version 330 core
			layout(location=0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";


		std::string vertShaderSrc = R"(
			#version 330 core
			layout(location=0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		m_shader.reset(new Shader(fragShaderSrc, vertShaderSrc));


		/* HACKING IN A TRIANGLE */




	}

	Application::~Application() 
	{

	}

	void Application::Run() 
	{
		while (m_running)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			/* HACKING IN A TRIANGLE */
			m_shader->Bind();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
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