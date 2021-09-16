#include "blpch.h"
#include "OpenGlContext.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Bolt {
	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window) {
		BL_CORE_ASSERT(window, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_Window);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BL_CORE_ASSERT(gladStatus, "Failed to initialize Glad!");

		BL_CORE_INFO("Using OpenGL");
		BL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		BL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		BL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_Window);
	}
}