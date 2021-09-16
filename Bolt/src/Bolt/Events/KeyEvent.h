#pragma once
#include "Bolt/Events/Event.h"

namespace Bolt {
	class KeyEvent : public Event {
	public:
		inline int GetKeyCode() { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		EVENT_CLASS_TYPE(KeyPressed)
		KeyPressedEvent(int keycode, int repeatCount): KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent(" << m_KeyCode << ", " << m_RepeatCount << ")";
			return ss.str();
		}

	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		EVENT_CLASS_TYPE(KeyReleased)
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent(" << m_KeyCode << ")";
			return ss.str();
		}
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		EVENT_CLASS_TYPE(KeyTyped)
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent(" << m_KeyCode << ")";
			return ss.str();
		}
	};
}