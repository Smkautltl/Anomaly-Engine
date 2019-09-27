#pragma once

#include "Anomaly/Core.h"
#include "Anomaly/Events/Event.h"

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

		virtual void OnUpdate()
		{
		}

		virtual void OnEvent(Event& event)
		{
		}

		const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
