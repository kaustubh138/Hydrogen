#pragma once

#ifdef H2_PLATFORM_WINDOWS
	#ifdef H2_BUILD_DLL
		#define H2_API __declspec(dllexport)	
	#else
		#define H2_API __declspec(dllimport)
	#endif
#else
	#error Platform not supported!
#endif

#ifdef H2_ENABLE_ASSERTS
	#define H2_ASSERT(x, ...) { if (!x) {H2_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}}
	#define H2_CORE_ASSERT(x, ...) { if (!x) { H2_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define H2_ASSERT(x, ...)	
	#define H2_CORE_ASSERT(x, ...)
#endif