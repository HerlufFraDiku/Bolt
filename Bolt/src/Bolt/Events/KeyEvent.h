#pragma once
#include "Event.h";
#include <sstream>;

namespace Bolt {
	class BOLT_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	class BOLT_API KeyPressedEvent : public KeyEvent {
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

	class BOLT_API KeyReleasedEvent : public KeyEvent {
	public:
		EVENT_CLASS_TYPE(KeyReleased)
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent(" << m_KeyCode << ")";
			return ss.str();
		}
	};
}