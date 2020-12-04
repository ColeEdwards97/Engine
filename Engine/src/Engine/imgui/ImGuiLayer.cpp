#include "engpch.h"

#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "Engine/Application.h"

// TEMP: should not reference glfw here
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine
{

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}


	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::onAttach()
	{

		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// enable keyboard controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	// enable gamepad controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// enable docking
		
																// TODO: possible imgui memory leak. RAM usage increases when window is moved outside main window
		// TODO: possibly confirmed issue with RivaTuner Statistics Server
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		// enable multiple viewports
		
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// style colors
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// when viewports are enabled set windowrounding and windowbg to match platform windows
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// get the native window so we can initialize imgui for opengl3
		Application& app = Application::get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());

		// platform and render bindings
		if (!m_ImGuiInitialized)
		{
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 410");
			m_ImGuiInitialized = true;
		}

	}

	void ImGuiLayer::onDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}


	void ImGuiLayer::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	
	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2((float) app.getWindow().getWidth(), (float) app.getWindow().getHeight());

		// rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}

	}


	void ImGuiLayer::onImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}


	void ImGuiLayer::onEvent(Event& e)
	{
		if (m_blockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.handled |= e.isInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.handled |= e.isInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}


}