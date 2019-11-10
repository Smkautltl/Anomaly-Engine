#pragma once

#include "RenderRequest.h"

namespace Anomaly
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submission(const std::shared_ptr<VertexArray>& vertexarray);		
		
		inline static RendererAPI::API GetRendererAPI() {return RendererAPI::GetAPI();}
	};
	
}