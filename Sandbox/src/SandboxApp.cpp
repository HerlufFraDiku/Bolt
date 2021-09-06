#include <Bolt.h>;

class ExampleLayer : public Bolt::Layer {
public:
	ExampleLayer() : Layer("Example layer") {}

	void OnUpdate() override {
		BL_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(Bolt::Event& event) override {
		BL_TRACE("{0}", event);
	}
};

class Sandbox : public Bolt::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Bolt::Application* Bolt::CreateApplication() {
	return new Sandbox();
}