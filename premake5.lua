workspace "GraphicsProg"
    architecture "x64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "OpenGL"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/bin-int/" .. outputdir .. "/%{prj.name}")
    targetname "OpenGL-Tutorial"

    local SourceDir = "src/"
    local TestDir   = (SourceDir .. "tests/")
    local ImguiDir  = "vendor/imgui/include/"

    files { 
        SourceDir .. "**.h", 
        SourceDir .. "**.cpp",
        ImguiDir .. "**.h",
        ImguiDir .. "**.cpp"
    }

    includedirs {
        SourceDir,
        "vendor/GLFW/include",
        "vendor/GLEW/include",
        "vendor/stb_image/include",
        "vendor/glm/include",
        "vendor/imgui/include"
    }

    libdirs { "lib/" }

    links { 
        "user32", 
        "opengl32", 
        "Gdi32", 
        "shell32", 
        "glfw3_mt", 
        "glew32s"
    }

    defines {
        "GLEW_STATIC",
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter { "configurations:Debug" }
        symbols "On"
        linkoptions { "-g" }

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
        removefiles { 
            TestDir .. "**.h",
            TestDir .. "**.cpp"
        }