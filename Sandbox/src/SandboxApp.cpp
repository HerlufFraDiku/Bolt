#include <Bolt.h>

#include "imgui/imgui.h"

class ExampleLayer : public Bolt::Layer {
public:
	ExampleLayer() : Layer("Example") { }

	void OnUpdate() override {
		if (Bolt::Input::IsKeyPressed(Bolt::Key::Tab))
			BL_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Bolt::Event& event) override {
		if (event.GetEventType() == Bolt::EventType::KeyPressed)
		{
			 Bolt::KeyPressedEvent& e = (Bolt::KeyPressedEvent&)event;
			if (e.GetKeyCode() == Bolt::Key::Tab)
				BL_TRACE("Tab key is pressed (event)!");
			BL_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Bolt::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() { }
};

Bolt::Application* Bolt::CreateApplication() {
	return new Sandbox();
}