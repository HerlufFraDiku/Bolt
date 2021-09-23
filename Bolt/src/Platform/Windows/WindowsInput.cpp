#include "blpch.h"
#include "Platform/Windows/WindowsInput.h"
#include "Bolt/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Bolt {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(KeyCode keycode) {
		BL_PROFILE_FUNCTION();

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button) {
		BL_PROFILE_FUNCTION();

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl() {
		BL_PROFILE_FUNCTION();

		auto [x, y] = GetMousePosition();
		return x;
	}

	float WindowsInput::GetMouseYImpl() {
		BL_PROFILE_FUNCTION();

		auto [x, y] = GetMousePosition();
		return y;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() {
		BL_PROFILE_FUNCTION();

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}
}