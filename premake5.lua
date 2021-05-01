workspace "ArkNet"
	location "build"
	debugdir ""
	platforms { "Win64", "Linux64" }
	configurations { "Debug", "Release" }
	
	filter { "platforms:Win64" }
		system "Windows"
		architecture "x86_64"

	
	filter { "platforms:Linux64" }
		system "linux"
		architecture "x86_64"
	
project "ArkNet"
	kind "SharedLib"
	language "C++"
	targetdir "build/bin/%{cfg.buildcfg}"
	objdir "build/obj/ArkNet/%{cfg.buildcfg}"
	files{
		"ArkNet/*.h",
		"ArkNet/*.cpp",
		"ArkNet/*/*.h",
		"ArkNet/*/*.cpp"
	}
	
	includedirs {
		"ArkNet"
	}
	
	defines { "BUILD_LIB" }

	filter "platforms:Linux64"
		defines {"SYSTEM_LINUX"}
	
	filter "platforms:Win64"
		defines {"SYSTEM_WIN"}
	
	filter "configurations:Debug"
		defines { "ARKNET_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		optimize "On"
	
	filter ""

project "TestAN"
	kind "ConsoleApp"
	targetdir "build/bin/%{cfg.buildcfg}"
	objdir "build/obj/TestAN/%{cfg.buildcfg}"
	language "C++"
	files{
		"TestAN/*.h",
		"TestAN/*.cpp",
		"TestAN/*/*.h",
		"TestAN/*/*.cpp"
	}
	
	includedirs {
		"ArkNet"
	}
	libdirs{
		"build/lib/%{cfg.buildcfg}"
	}
	links{
		"ArkNet"
	}
	
	filter "configurations:Debug"
		defines { "ARKNET_DEBUG" }
		symbols "On"


	filter "configurations:Release"
		optimize "On"
		
	filter ""
