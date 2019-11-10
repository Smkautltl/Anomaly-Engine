#pragma once

#include "../RendererAPI.h"

namespace Anomaly
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColour(const glm::vec4& colour) override;
		virtual void Clear() override;

		virtual void DrawCall(const std::shared_ptr<VertexArray>& vertexarray) override;
	};
}