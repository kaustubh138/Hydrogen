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

include "Hydrogen/vendor/GLFW"

project "Hydrogen"
	location "Hydrogen"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.hpp"
	pchsource "%{prj.name}/src/pch/pch.cpp"

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{prj.name}/src/Hydrogen",
		"%{prj.name}/src/pch",
		"%{IncludeDirs.GLFW}"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"H2_PLATFORM_WINDOWS",
			"H2_BUILD_DLL",
			"H2_ENABLE_ASSERTS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "H2_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "H2_RELEASE"
		buildoptions "/MDd"
		optimize "On"

	filter "configurations:Dist"
		defines "H2_DIST"
		buildoptions "/MDd"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Hydrogen/src"
	}

	links
	{
		"Hydrogen"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"H2_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "H2_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "H2_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "H2_DIST"
		optimize "On" 