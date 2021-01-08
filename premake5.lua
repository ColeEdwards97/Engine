workspace "Engine"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
includeDir = {}
includeDir["glad"] = "Engine/vendor/glad/include"
includeDir["glfw"] = "Engine/vendor/glfw/include"
includeDir["glm"] = "Engine/vendor/glm"
includeDir["imgui"] = "Engine/vendor/imgui"
includeDir["stb_image"] = "Engine/vendor/stb_image"

group "Dependencies"
	include "Engine/vendor/glad"
	include "Engine/vendor/glfw"
	include "Engine/vendor/imgui"

group ""

-- ENGINE PROJECT -------------------------------
project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "engpch.h"
	pchsource "Engine/src/engpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{includeDir.glad}",
		"%{includeDir.glfw}",
		"%{includeDir.glm}",
		"%{includeDir.imgui}",
        "%{includeDir.stb_image}"
	}
	
    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }
    
	links
	{
		"glad",
		"GLFW",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"ENG_PLATFORM_WINDOWS",
			"ENGINE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines "ENG_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "ENG_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "ENG_DIST"
		runtime "Release"
		optimize "on"
		

-- SANDBOX PROJECT ------------------------------
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" ..outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Engine/vendor/spdlog/include",
		"Engine/src",
        "Engine/vendor",
		"%{includeDir.glm}"
	}
	
	links 
	{
		"Engine"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"ENG_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "ENG_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "ENG_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "ENG_DIST"
		runtime "Release"
		optimize "on"