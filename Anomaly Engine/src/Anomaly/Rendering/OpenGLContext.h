#pragma once
#include "RenderingContext.h"

struct GLFWwindow;

namespace  Anomaly
{
	class OpenGLContext : public RenderingContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		
		virtual void Init() override;
		virtual void Swapbuffers() override;
	private:
		GLFWwindow* m_window;
	};
}
