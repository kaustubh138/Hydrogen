#pragma once

#include <memory>

#ifdef H2_PLATFORM_WINDOWS
#ifdef H2_DYNAMIC_LINK
	#ifdef H2_BUILD_DLL
		#define H2_API __declspec(dllexport)	
	#else
		#define H2_API __declspec(dllimport)
	#endif
#else
#define H2_API
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

#define H2_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// Hydrogen Types
namespace Hydrogen
{
	template<class T>
	using Scope = std::unique_ptr<T>;
	
	template<class T>
	using Ref = std::shared_ptr<T>;
}