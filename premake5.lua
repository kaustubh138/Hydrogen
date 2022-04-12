workspace "Hydrogen"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hydrogen"
	location "Hydrogen"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include",
		"{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"H2_PLATFORM_WINDOWS",
			"H2_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
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