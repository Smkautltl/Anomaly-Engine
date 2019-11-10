#include "aepch.h"
#include "RenderRequest.h"

#include "OpenGL/OpenGLRendererAPI.h"

namespace Anomaly
{
	RendererAPI* RenderRequest::s_RendererAPI = new OpenGLRendererAPI;
}