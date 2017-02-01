workspace "nart"
	language "C++"

	location "build"
	targetdir "bin"
	objdir "build"

	configurations { "Release" }

	flags { "C++14" }

	sysincludedirs { "/usr/local/include" }
	libdirs { "/usr/local/lib" }

	include "nart.lua"