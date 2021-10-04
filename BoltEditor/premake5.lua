project "BoltEditor"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"%{wks.location}/Bolt/vendor/spdlog/include",
		"%{wks.location}/Bolt/src",
		"%{wks.location}/Bolt/vendor",
		"%{IncludeDir.glm}",
        "%{IncludeDir.entt}"
	}

	links { "Bolt" }

	filter "system:windows"
		systemversion "latest"
		defines {
			"BL_PLATFORM_WINDOWS"
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