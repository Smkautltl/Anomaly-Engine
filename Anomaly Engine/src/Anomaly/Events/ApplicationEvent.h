#pragma once

#include "Event.h"

namespace Anomaly
{
	//===WINDOW=EVENTS==================================================
	class ANOMALY_API WindowResizeEvent : public Event
	{
	public:
		//When this event is called it will set the events width and height
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{
		}

		//These will return the width and height 
		[[nodiscard]] unsigned int GetWidth() const { return m_Width; }
		[[nodiscard]] unsigned int GetHeight() const { return m_Height; }

		//This will return the width and height in string form
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResize: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		//Sets the events type and category
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	class ANOMALY_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		= default;

		//Sets the events type and category
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


	//==================================================================

	//=APPLICATION=EVENTS===============================================
	class ANOMALY_API ApplicationTickEvent : public Event
	{
	public:
		ApplicationTickEvent()
		= default;

		//Sets the events type and category
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ANOMALY_API ApplicationUpdateEvent : public Event
	{
	public:
		ApplicationUpdateEvent()
		= default;

		//Sets the events type and category
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ANOMALY_API ApplicationRenderEvent : public Event
	{
	public:
		ApplicationRenderEvent()
		= default;

		//Sets the events type and category
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	//==================================================================
}
