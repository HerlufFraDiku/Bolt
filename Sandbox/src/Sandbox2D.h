#pragma once
#include "Bolt.h"

class Sandbox2D : public Bolt::Layer {
public:
	Sandbox2D();
	virtual void OnUpdate(Bolt::Timestep deltaTime) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Bolt::Event& event) override;

private:
	glm::vec4 m_QuadColor;
	Bolt::Ref<Bolt::Texture2D> m_CheckerTex;
	Bolt::OrthographicCameraController m_CameraController;
	Bolt::FPSCounter m_FPSCounter;
};

