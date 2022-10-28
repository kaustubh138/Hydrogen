workspace "Hydrogen"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "Hydrogen/vendor/GLFW/include"
IncludeDirs["Glad"] = "Hydrogen/vendor/Glad/include"
IncludeDirs["ImGUI"] = "Hydrogen/vendor/ImGUI"
IncludeDirs["glm"] = "Hydrogen/vendor/glm"

group "Dependencies"
	defines {
		"IMGUI_API=__declspec(dllexport)"
	}

	include "Hydrogen/vendor/GLFW"
	include "Hydrogen/vendor/Glad"
	include "Hydrogen/vendor/ImGUI"

group ""

project "Hydrogen"
	location "Hydrogen"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.hpp"
	pchsource "%{prj.name}/src/Engine/pch/pch.cpp"

	defines "_CRT_SECURE_NO_WARNINGS"

	links
	{
		"GLFW",
		"Glad",
		"ImGUI",
		"opengl32.lib"
	}

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{prj.name}/src/Engine",
		"%{prj.name}/src/Engine/Platform",
		"%{prj.name}/src/Engine/pch",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.Glad}",
		"%{IncludeDirs.ImGUI}",
		"%{IncludeDirs.glm}"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"H2_PLATFORM_WINDOWS",
			"H2_BUILD_DLL",
			"H2_ENABLE_ASSERTS"
		}

	filter "configurations:Debug"
		defines "H2_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "H2_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "H2_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hydrogen/vendor/spdlog/include",
		"Hydrogen/src",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.ImGUI}"
	}

	links
	{
		"Hydrogen"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"H2_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "H2_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "H2_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "H2_DIST"
		runtime "Release"
		optimize "On" 