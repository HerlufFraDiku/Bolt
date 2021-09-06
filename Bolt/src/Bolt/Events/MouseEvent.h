#pragma once
#include "Bolt/Events/Event.h";

namespace Bolt {

	class BOLT_API MouseMovedEvent : public Event {
	public:
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
		
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
		inline float GetMouseX() { return m_MouseX; }
		inline float GetMouseY() { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMoveEvent(" << m_MouseX << "," << m_MouseY << ")";
			return ss.str();
		}

	private:
		float m_MouseX, m_MouseY;
	};

	class BOLT_API MouseScrolledEvent : public Event {
	public:
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

		MouseScrolledEvent(float offsetX, float offsetY) : m_OffsetX(offsetX), m_OffsetY(offsetY) {}
		inline float GetMouseX() { return m_OffsetX; }
		inline float GetMouseY() { return m_OffsetY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMoveEvent(" << m_OffsetX << "," << m_OffsetY << ")";
			return ss.str();
		}

	private:
		float m_OffsetX, m_OffsetY;
	};

	class BOLT_API MouseButtonEvent : public Event {
	public:
		inline int GetButton() { return m_Button; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(int button) : m_Button(button) {}
		int m_Button;
	};

	class BOLT_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		EVENT_CLASS_TYPE(MouseButtonPressed)
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent(" << m_Button << ")";
			return ss.str();
		}
	};

	class BOLT_API MouseButtonReleasedEvent: public MouseButtonEvent {
	public:
		EVENT_CLASS_TYPE(MouseButtonReleased)
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent(" << m_Button << ")";
			return ss.str();
		}
	};
}