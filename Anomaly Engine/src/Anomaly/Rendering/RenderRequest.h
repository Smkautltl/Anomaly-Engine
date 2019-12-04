#pragma once

#include "RendererAPI.h"

namespace Anomaly
{
	class RenderRequest
	{
	public:
		inline static void SetClearColour(const glm::vec4& colour)															{ s_RendererAPI->SetClearColour(colour); }
		inline static void Clear()																							{ s_RendererAPI->Clear(); }		
		inline static void DrawCall(const std::shared_ptr<VertexArray>& vertexarray, const std::shared_ptr<Shader>& shader)	{ s_RendererAPI->DrawCall(vertexarray, shader); }
	private:
		static RendererAPI* s_RendererAPI;
	};
	
}