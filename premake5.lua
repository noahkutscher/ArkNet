workspace "ArkNet"
	location "build"
	configurations { "Debug", "Release" }
	
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
	
	filter "configurations:Debug"
		defines { "SF_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		optimize "On"
	
	filter ""

project "TestSF"
	kind "ConsoleApp"
	targetdir "build/bin/%{cfg.buildcfg}"
	objdir "build/obj/TestSF/%{cfg.buildcfg}"
	language "C++"
	files{
		"test_sf/*.h",
		"test_sf/*.cpp",
		"test_sf/*/*.h",
		"test_sf/*/*.cpp"
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
		defines { "SF_DEBUG" }
		symbols "On"


	filter "configurations:Release"
		optimize "On"
		
	filter ""
