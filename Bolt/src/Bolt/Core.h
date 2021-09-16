#pragma once

#ifdef BL_PLATFORM_WINDOWS
	#ifdef BL_BUILD_DLL
		#define BOLT_API __declspec(dllexport)
	#else
		#define BOLT_API __declspec(dllimport)
	#endif
#else
	#error Bolt only supports Windows!
#endif

#define BIT(x) (1 << x)

#ifdef HZ_DEBUG
	#define BL_ENABLE_ASSERTS
#endif

#ifdef BL_ENABLE_ASSERTS
	#define BL_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BL_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BL_ASSERT(x, ...)
	#define BL_CORE_ASSERT(x, ...)
#endif

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
