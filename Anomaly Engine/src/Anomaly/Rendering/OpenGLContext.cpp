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

		AE_CORE_INFO("OpenGL Renderer: {0}\n\t\t\t   Graphics Chip: {1} \n\t\t\t   OpenGL Version: {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		
		glfwSwapBuffers(m_window);
	}
}
