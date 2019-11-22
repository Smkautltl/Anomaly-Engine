#pragma once

#include "Anomaly/Core.h"
#include "Anomaly/Events/Event.h"
#include "Core/TimeStep.h"

namespace Anomaly
{
	//This a base for layers
	class ANOMALY_API Layer
	{
	public:
		explicit Layer(std::string debugname = "Layer");
		virtual ~Layer();

		virtual void OnAttach()
		{
		}

		virtual void OnDetach()
		{
		}

		virtual void OnUpdate(TimeStep deltatime)
		{
		}

		virtual void OnEvent(Event& event)
		{
		}

		virtual void OnImGuiRender()
		{
		}

		const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
