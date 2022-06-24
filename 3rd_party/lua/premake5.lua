-- premake5.lua

local LUA = {
    CORE =    { "src/lapi.c", "src/lcode.c", "src/ldebug.c", "src/ldo.c", "src/ldump.c", "src/lfunc.c", "src/lgc.c", "src/llex.c", "src/lmem.c", "src/lobject.c", "src/lopcodes.c", "src/lparser.c", "src/lstate.c", "src/lstring.c", "src/ltable.c", "src/ltm.c", "src/lundump.c", "src/lvm.c", "src/lzio.c" },
    LIB =     { "src/lauxlib.c", "src/lbaselib.c", "src/ldblib.c", "src/liolib.c", "src/lmathlib.c", "src/loslib.c", "src/lstrlib.c", "src/ltablib.c", "src/loadlib.c", "src/linit.c" },
    LUA =     { "src/lua.c" },
    LUAC =    { "src/luac.c" }
}

workspace "lua"
   location "project"
   configurations { "Release" }

project "lua51"
   location "project"
   kind "StaticLib"
   language "C++"
   architecture "x64"
   targetdir "lib/"
   systemversion "10.0.19041.0"
   characterset "MBCS"
   cppdialect "C++17"
   
   files { LUA.CORE, LUA.LIB }

   filter "configurations:Release"
      optimize "On"