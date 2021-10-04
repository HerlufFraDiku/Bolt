project "Bolt"
    kind "StaticLib"
    staticruntime "on"
    language "C++"
    cppdialect "C++17"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "blpch.h"
    pchsource "src/blpch.cpp"

    files {
        "src/**.h",
        "src/**.cpp",
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl",		
        "vendor/stb_image/**.h",
        "vendor/stb_image/**.cpp"
    }

    includedirs {
        "src",
        "vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "BL_PLATFORM_WINDOWS",
            "BL_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "BL_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BL_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "BL_DIST"
        runtime "Release"
        optimize "on"
