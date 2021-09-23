#include "blpch.h"
#include <GLFW/glfw3.h>
#include <Glad/glad.h>
#include "Platform/OpenGL/OpenGlContext.h"

namespace Bolt {
	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window) {
		BL_CORE_ASSERT(window, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		BL_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_Window);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BL_CORE_ASSERT(gladStatus, "Failed to initialize Glad!");

		BL_CORE_INFO("Using OpenGL");
		BL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		BL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		BL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		BL_PROFILE_FUNCTION();

		glfwSwapBuffers(m_Window);
	}
}