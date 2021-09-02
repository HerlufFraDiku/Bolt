#pragma once
#include "Bolt/Events/Event.h";
#include <sstream>;

namespace Bolt {
	class BOLT_API WindowResizeEvent : public Event {
	public:
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		WindowResizeEvent(unsigned int width, unsigned int height): m_Width(width), m_Height(height) {}
		inline unsigned int GetWidth() { return m_Width; }
		inline unsigned int GetHeight() { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent(" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}

	private:
		unsigned int m_Width, m_Height;
	};

	class BOLT_API WindowCloseEvent : public Event {
	public:
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		WindowCloseEvent(){}
	};

	class BOLT_API AppTickEvent : public Event {
	public:
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		AppTickEvent() {}
	};

	class BOLT_API AppUpdateEvent : public Event {
	public:
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		AppUpdateEvent() {}
	};

	class BOLT_API AppRenderEvent : public Event {
	public:
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		AppRenderEvent() {}
	};
}