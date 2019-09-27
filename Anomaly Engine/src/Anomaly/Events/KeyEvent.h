#pragma once
#include "Event.h"

namespace Anomaly
{
	//This class is not really an event that can be called it just a base for the pressed and released events below 
	class ANOMALY_API KeyEvent : public Event
	{
	public:
		//Returns the keycode to the place it is called 
		[[nodiscard]] int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		explicit KeyEvent(int KeyCode)
			: m_KeyCode(KeyCode)
		{
		}

		int m_KeyCode;
	};

	//This event is a child of the key event class and sorts out keys pressed down
	class ANOMALY_API KeyPressedEvent final : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount)
		{
		}

		[[nodiscard]] int GetRepeatCount() const { return m_RepeatCount; }

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Pressed Event: " << m_KeyCode << " ( " << m_RepeatCount << " repeats )";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	//This is the same and the pressed event but on key releases
	class ANOMALY_API KeyReleasedEvent final : public KeyEvent
	{
	public:
		explicit KeyReleasedEvent(int KeyCode)
			: KeyEvent(KeyCode)
		{
		}

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Released Event: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class ANOMALY_API KeyTypedEvent final : public KeyEvent
	{
	public:
		explicit KeyTypedEvent(int KeyCode)
			: KeyEvent(KeyCode)
		{
		}

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Typed Event: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
