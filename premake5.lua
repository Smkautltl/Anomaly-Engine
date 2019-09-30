workspace "Anomaly Engine"
 architecture "x64"

 configurations
 {
  "Debug",
  "Release",
  "Dist"
 }

 outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

 -- Include directories relative to root folder (sln DIR)
 IncludeDir = {}
 IncludeDir["GLFW"] = "Anomaly Engine/vendor/GLFW/include"
 IncludeDir["GLAD"] = "Anomaly Engine/vendor/GLAD/include"
 IncludeDir["ImGui"] = "Anomaly Engine/vendor/imgui"
 IncludeDir["glm"] = "Anomaly Engine/vendor/glm"
 
 include "Anomaly Engine/vendor/GLFW"
 include "Anomaly Engine/vendor/GLAD"
 include "Anomaly Engine/vendor/imgui"
 
 project "Anomaly Engine"
 location "Anomaly Engine"
 kind "SharedLib"
 language "C++"

 targetdir ("bin/" .. outputdir .. "/%{prj.name}")
 objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

 pchheader "aepch.h"
 pchsource "Anomaly Engine/src/aepch.cpp"

 files
 {
  "%{prj.name}/src/**.h",
  "%{prj.name}/src/**.cpp"
 }

 includedirs
 {

  "%{prj.name}/src",
  "%{prj.name}/vendor/spdlog/include",
  "%{IncludeDir.GLFW}",
  "%{IncludeDir.GLAD}",
  "%{IncludeDir.ImGui}",
  "%{IncludeDir.glm}"
 }
 
 links
 {
	"GLFW",
	"GLAD",
	"ImGui",
	"opengl32.lib"
 }

 filter "system:windows"
  cppdialect "C++17"
  staticruntime "On"
  systemversion "latest"

  defines
  {
   "AE_PLATFORM_WINDOWS",
   "AE_BUILD_DLL",
   "GLFW_INCLUDE_NONE"
  }

  postbuildcommands
  {
   ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
  }

 filter "configurations:Debug"
  defines "AE_DEBUG"
  buildoptions "/MDd"
  symbols "On"

 filter "configurations:Release"
  defines "AE_RELEASE"
  buildoptions "/MD"
  optimize "On"

 filter "configurations:Dist"
  defines "AE_DIST"
  buildoptions "/MD"
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
  "Anomaly Engine/src",
  "Anomaly Engine/vendor",
   "%{IncludeDir.glm}"
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
  buildoptions "/MDd"
  symbols "On"

 filter "configurations:Release"
  defines "AE_RELEASE"
  buildoptions "/MD"
  optimize "On"

 filter "configurations:Dist"
  defines "AE_DIST"
  buildoptions "/MD"
  optimize "On"