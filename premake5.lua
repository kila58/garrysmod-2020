-- premake5.lua
workspace "garrysmod"
   location "project"
   configurations { "Release" }

project "garrysmod"
   location "project"
   kind "SharedLib"
   language "C++"
   architecture "x64"
   targetdir "bin/"
   systemversion "10.0.19041.0"
   characterset "MBCS"
   cppdialect "C++20"
   
   files { "src/**.hpp", "src/**.cpp" }

   includedirs { "3rd_party/" }
   libdirs { "3rd_party/" }

   -- lua
   links { "3rd_party/lua/lib/lua51" }

   filter "configurations:Release"
      optimize "On"
