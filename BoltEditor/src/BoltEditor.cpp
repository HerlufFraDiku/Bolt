#include <Bolt.h>
#include <Bolt/Core/Entrypoint.h>
#include "EditorLayer.h"

namespace Bolt {
	class BoltEditor : public Application {
	public: 
		BoltEditor() {
			PushLayer(new EditorLayer());
		}

		~BoltEditor() {}

	};

	Application* CreateApplication() {
		return new BoltEditor();
	}
}