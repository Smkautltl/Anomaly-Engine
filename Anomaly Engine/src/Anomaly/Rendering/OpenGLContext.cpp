#include "aepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace  Anomaly
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		:m_window(window)
	{
		AE_CORE_ASSERT(window, "Window is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AE_CORE_ASSERT(status, "Failed to initialise GLAD!")
	}

	void OpenGLContext::Swapbuffers()
	{
		
		glfwSwapBuffers(m_window);
	}
}
