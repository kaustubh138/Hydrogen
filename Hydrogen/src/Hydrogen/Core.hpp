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