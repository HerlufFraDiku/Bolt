#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Bolt/Core/Log.h"
#include "Bolt/Debug/Instrumentation.h"

#ifdef BL_PLATFORM_WINDOWS
	#include <Windows.h>
#endif