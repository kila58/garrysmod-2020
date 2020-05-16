-- premake5.lua
workspace "garrysmod"
   location "project"
   configurations { "Release" }

project "garrysmod"
   location "project"
   kind "SharedLib"
   language "C++"
   architecture "x86"
   targetdir "bin/"
   systemversion "10.0.16299.0"
   characterset "MBCS"
   cppdialect "C++17"
   
   files { "src/**.hpp", "src/**.cpp" }

   filter "configurations:Release"
      optimize "On"
