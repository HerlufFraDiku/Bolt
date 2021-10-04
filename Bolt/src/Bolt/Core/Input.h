#pragma once
#include "Bolt/Core/Core.h"
#include "Bolt/Core/KeyCodes.h"
#include "Bolt/Core/MouseCodes.h"

// This input class is implemented per platform. See Platform/.../Input.cpp for implementation.
namespace Bolt {
	class Input {
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static float GetMouseX();
		static float GetMouseY();
		static std::pair<float, float> GetMousePosition();
	};
}