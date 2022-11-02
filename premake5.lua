workspace "GlfwTemplate"
    architecture "x86_64"
    configurations {"Debug", "Release"}

    filter { "configurations:Debug" }
    symbols "On"

    filter { "configurations:Release" }
    optimize "On"

    flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include "src/vendor/imgui"

project "GLprogram"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"

    pchheader "pch.h"
    pchsource "%{prj.name}/src/pch.cpp"
    -- i hardcode all files nessecary, should be done with submodules later
    files 
    {
        "src/**.h",
        "src/**.cpp",
        -- "src/renderer/*.h",
        -- "src/renderer/*.cpp",
        -- "src/vendor/stb_image/**.h",
        -- "src/vendor/stb_image/**.cpp",
        -- "src/vendor/glm/glm/**.hpp",
        -- "src/vendor/glm/glm/**.inl",
        -- "src/vendor/imgui/**.h",
        -- "src/vendor/imgui/**.cpp",
        -- "src/tests/**.cpp",
        -- "src/tests/**.h",
    }

    includedirs 
    {
        -- "%{prj.name}/src",
        "src",
        -- "src/renderer",
        "%{prj.name}/src/vendor/imgui",
        --"%{prj.name}/src/vendor/stb_image",
        -- "%{prj.name}/src/vendor/imgui",
        -- "%{prj.name}/src/vendor/glm",
        -- "%{prj.name}/src/tests",
    }

    filter { "system:linux" }
        links { "glfw", "GLEW", "GLU", "X11", "OpenGL", "dl", }
    
    -- filter { "system:windows" }
    --     links { "glfw", "GLEW", "GLU", "opengl32.lib" }
    
    objdir ("obj/" .. outputdir .. "/%{prj.name}")
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")