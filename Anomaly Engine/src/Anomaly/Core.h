#pragma once

#ifdef AE_PLATFORM_WINDOWS
	#ifdef AE_BUILD_DLL
		#define ANOMALY_API __declspec(dllexport)
	#else
		#define ANOMALY_API __declspec(dllimport)
	#endif
#else
	#error Anomaly Engine only supports windows!
#endif