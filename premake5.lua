workspace "Anomaly Engine"
 architecture "x64"

 configurations
 {
  "Debug",
  "Release",
  "Dist"
 }

 outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

 project "Anomaly Engine"
 location "Anomaly Engine"
 kind "SharedLib"
 language "C++"

 targetdir ("bin/" .. outputdir .. "/%{prj.name}")
 objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

 files
 {
  "%{prj.name}/src/**.h",
  "%{prj.name}/src/**.cpp"
 }

 includedirs
 {

  "%{prj.name}/src",
  "%{prj.name}/vendor/spdlog/include"
 }

 filter "system:windows"
  cppdialect "C++17"
  staticruntime "On"
  systemversion "latest"

  defines
  {
   "AE_PLATFORM_WINDOWS",
   "AE_BUILD_DLL"
  }

  postbuildcommands
  {
   ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
  }

 filter "configurations:Debug"
  defines "AE_DEBUG"
  symbols "On"

 filter "configurations:Release"
  defines "AE_RELEASE"
  optimize "On"

 filter "configurations:Dist"
  defines "AE_DIST"
  optimize "On"

project "Sandbox"
 location "Sandbox"
 kind "ConsoleApp"
 language "C++"

 targetdir ("bin/" .. outputdir .. "/%{prj.name}")
 objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

 files
 {
  "%{prj.name}/src/**.h",
  "%{prj.name}/src/**.cpp"
 }

 includedirs
 {
  "Anomaly Engine/vendor/spdlog/include",
  "Anomaly Engine/src"
 }

 links
 {
  "Anomaly Engine"
 }

 filter "system:windows"
  cppdialect "C++17"
  staticruntime "On"
  systemversion "latest"

  defines
  {
   "AE_PLATFORM_WINDOWS"
  }

 filter "configurations:Debug"
  defines "AE_DEBUG"
  symbols "On"

 filter "configurations:Release"
  defines "AE_RELEASE"
  optimize "On"

 filter "configurations:Dist"
  defines "AE_DIST"
  optimize "On"