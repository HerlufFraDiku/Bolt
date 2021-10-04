#include "blpch.h"
#include "Bolt/Core/Input.h"
#include "Bolt/Core/Application.h"
#include <GLFW/glfw3.h>

#ifdef BL_PLATFORM_WINDOWS
namespace Bolt {

	bool Input::IsKeyPressed(KeyCode keycode) {
		BL_PROFILE_FUNCTION();

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button) {
		BL_PROFILE_FUNCTION();

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float Input::GetMouseX() {
		BL_PROFILE_FUNCTION();

		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY() {
		BL_PROFILE_FUNCTION();

		auto [x, y] = GetMousePosition();
		return y;
	}

	std::pair<float, float> Input::GetMousePosition() {
		BL_PROFILE_FUNCTION();

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}
}
#endif // BL_PLATFORM_WINDOWS