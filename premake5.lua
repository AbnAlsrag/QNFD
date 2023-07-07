workspace "QNFD"
    configurations { "Debug", "Dev", "Release" }

    architecture "x64"
    startproject "QNFD"
    compileas "C"
    
    output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- //QNFD// --
    project "QNFD"
        kind "ConsoleApp"
        language "C"
        
        targetdir ("bin/" .. output_dir .. "/%{prj.name}")
        objdir ("bin-int/" .. output_dir .. "/%{prj.name}")
    
        files {
            "src/**.h",
            "src/**.c",
        }

        includedirs {
            "external/"
        }

        libdirs {
            "external/"
        }

        links {
            "raylib/lib/msvc/raylibdll",
        }
        
        filter "system:windows"
            systemversion "latest"
            
            defines {
                "QNFD_PLATFORM_WINDOWS"
            }
 
        filter "configurations:Debug"
            defines { "QNFD_Debug" }
            boundscheck "On"
            symbols "On"
            
        filter "configurations:Dev"
            defines { "QNFD_Dev" }
            boundscheck "Off"
            optimize "Debug"

        filter "configurations:Release"
            defines { "QNFD_Release" }
            boundscheck "Off"
            optimize "Full"