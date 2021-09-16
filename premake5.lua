workspace "Bolt"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to the root
IncludeDir = {}
IncludeDir["GLFW"] = "Bolt/vendor/GLFW/include"
IncludeDir["Glad"] = "Bolt/vendor/Glad/include"
IncludeDir["ImGui"] = "Bolt/vendor/imgui"
IncludeDir["glm"] = "Bolt/vendor/glm"

include "Bolt/vendor/GLFW"
include "Bolt/vendor/Glad"
include "Bolt/vendor/imgui"

project "Bolt"
	location "Bolt"
	kind "SharedLib"
	staticruntime "off"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "blpch.h"
	pchsource "Bolt/src/blpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"BL_PLATFORM_WINDOWS",
			"BL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "BL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "BL_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	staticruntime "off"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	links "Bolt"

	includedirs {
		"Bolt/vendor/spdlog/include",
		"%{IncludeDir.glm}",
		"Bolt/vendor",
		"Bolt/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"BL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "BL_DIST"
		runtime "Release"
		optimize "On"