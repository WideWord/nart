project "nart"
	kind "SharedLib"

	files { "../nart/source/**.cpp", "../nart/source/**.hpp", "../nart/include/**.hpp" }
	includedirs { "../nart/include/nart" }

	filter "system:macosx"
		defines "NART_PLATFORM_OSX"
	filter {}


	links { "glfw", "glew" }

	filter "system:macosx"
		links { "OpenGL.framework" }
	filter "system:windows"
		links { "OpenGL32" }
	filter "system:linux"
		links { "GL" }
	filter {}