#pragma once

#include "aepch.h"
#include "../Core/Core.h"

namespace Anomaly
{
	//The events that are made are blocking so that event will be done there and then

	//Enum of all the event types that will be in the engine
	enum class EventType
	{
		None = 0,

		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,

		AppTick,
		AppUpdate,
		AppRender,

		KeyPressed,
		KeyReleased,
		KeyTyped,

		MouseButtonPressed,
		MouseButtonReleased,
		MouseMove,
		MouseScroll
	};

	//Enum of all the event categories in the engine
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	//This macro will take in the event type and return the static type
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }
	//This macro will take in a category and return category flags
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	//This is a base class for events
	class ANOMALY_API Event
	{
	public:
		virtual ~Event() = default;
		bool Handled = false;

		//This functions will be overridden by other classes to setup the event
		[[nodiscard]] virtual EventType GetEventType() const = 0;
		[[nodiscard]] virtual const char* GetName() const = 0;
		[[nodiscard]] virtual int GetCategoryFlags() const = 0;
		[[nodiscard]] virtual std::string ToString() const { return GetName(); }

		//Checks to see if the event is in the given categories
		bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}
	};

	//This dispatches events and returns if the event has been handled or not
	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		explicit EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*static_cast<T*>(&m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
