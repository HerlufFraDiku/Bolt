#pragma once
#include <Bolt.h>


namespace Bolt {
	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual void OnUpdate(Timestep deltaTime) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	private:
		void RenderViewport();

		bool m_ViewportHovered = false, m_ViewportFocused = false;

		glm::vec2 m_ViewportSize;
		OrthographicCameraController m_CameraController;
		FPSCounter m_FPSCounter;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_Square;

		Entity m_CameraEntity;
	};
}