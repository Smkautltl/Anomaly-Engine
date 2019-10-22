#pragma once

//This checks to see if engine dll needs to be exported or imported
#ifdef AE_PLATFORM_WINDOWS
	#if AE_DYNAMIC_LNK
		#ifdef AE_BUILD_DLL
			#define ANOMALY_API __declspec(dllexport)
		#else
			#define ANOMALY_API __declspec(dllimport)
		#endif
	#else
		#define ANOMALY_API
	#endif
#else
	#error Anomaly Engine only supports windows!
#endif

//Enables and disables ASSERTS
#ifdef AE_ENABLE_ASSERTS
	#define AE_ASSERT(x, ...) { if(!(x)) { AE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define AE_CORE_ASSERT(x, ...) { if(!(x)) { AE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define AE_ASSERT(x, ...)
#define AE_CORE_ASSERT(x, ...)
#endif

//bit shifts 1 by n
#define BIT(n) (1 << n)

//Binds an function to this 
#define AE_BIND_EVENT_FN(function) std::bind(&function, this,  std::placeholders::_1)
