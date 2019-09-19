#pragma once

#include "Event.h"
#include <sstream>

namespace Anomaly
{

//===WINDOW=EVENTS==================================================
	class ANOMALY_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResize: " << m_Width <<", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	class ANOMALY_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
//==================================================================

//=APPLICATION=EVENTS===============================================
	class ANOMALY_API ApplicationTickEvent : public Event
	{
	public:
		ApplicationTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ANOMALY_API ApplicationUpdateEvent : public Event
	{
	public:
		ApplicationUpdateEvent() {}
		
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ANOMALY_API ApplicationRenderEvent : public Event
	{
	public:
		ApplicationRenderEvent() {}
		
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
//==================================================================
}