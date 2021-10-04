include "dependencies.lua"

workspace "Bolt"
	architecture "x86_64"
	startproject "BoltEditor"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Bolt/vendor/GLFW"
	include "Bolt/vendor/Glad"
	include "Bolt/vendor/imgui"
group ""

include "Bolt"
include "BoltEditor"
include "Sandbox"


