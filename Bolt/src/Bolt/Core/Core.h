#pragma once

#include <memory>

#ifdef BL_PLATFORM_WINDOWS

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

namespace Bolt {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Scope<T> CreateScope(Args&&... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Ref<T> CreateRef(Args&&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

typedef uint32_t BLenum;
#define BL_STATIC 0
#define BL_DYNAMIC 1