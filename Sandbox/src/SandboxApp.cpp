#include <Bolt.h>;

class Sandbox : public Bolt::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Bolt::Application* Bolt::CreateApplication() {
	return new Sandbox();
}