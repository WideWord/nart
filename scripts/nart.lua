project "nart"

	local PROJ_DIR = path.getabsolute("..")

	language "C++"

	kind "SharedLib"

	buildoptions_cpp {
	    "-std=c++14",
	}

	if os.is("macosx") then
		defines "NART_PLATFORM_OSX"
	end

	files {
		path.join(PROJ_DIR, "source/**.cpp"),
		path.join(PROJ_DIR, "source/**.hpp"),
		path.join(PROJ_DIR, "include/**.hpp"),
	}
	
	includedirs { path.join(PROJ_DIR, "include") }

	links { "glfw", "glew" }
	

	if os.is("macosx") then
		links { "OpenGL.framework" }
		libdirs { "/usr/local/lib" }
		includedirs { "/usr/local/include" }
	end

