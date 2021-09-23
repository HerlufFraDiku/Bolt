#include <Bolt.h>
#include <Bolt/Core/Entrypoint.h>

#include "Sandbox2D.h"


class Sandbox : public Bolt::Application {
public:
	Sandbox() {
		PushLayer(new Sandbox2D());
	}

	~Sandbox() { }
};

Bolt::Application* Bolt::CreateApplication() {
	return new Sandbox();
}