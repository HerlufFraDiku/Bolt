#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D() :
	Bolt::Layer("Sandbox2D"),
	m_CameraController(1280.0f / 720.0f),
	m_FPSCounter(),
	m_CheckerTex(Bolt::Texture2D::Create("assets/textures/checkerboard.png")),
	m_QuadColor(glm::vec4(0.3f, 0.3f, 0.8f, 1.0f)),
	m_Batch(100000)
{}

void Sandbox2D::OnUpdate(Bolt::Timestep dt) {
	m_CameraController.OnUpdate(dt);
	m_FPSCounter.OnUpdate(dt);

	Bolt::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Bolt::RenderCommand::Clear();

	Bolt::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		BL_PROFILE_SCOPE("For loop QUADS");
		for (int x = 0; x < 100; x++) {
			for (int y = 0; y < 100; y++) {
				m_Batch.AddQuad(
					Bolt::Quad(
						glm::vec2(x * 0.11f - 5.5f, y * 0.11f - 5.5f), // Position
						glm::vec2(0.1f),							   // Size
						m_QuadColor									   // Color
					));
			}
		}
	}

	m_Batch.Flush();

	Bolt::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Controls");
	ImGui::Text("%.1f FPS", m_FPSCounter.FPS());
	ImGui::ColorEdit4("QuadColor", glm::value_ptr(m_QuadColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Bolt::Event& event) {
	m_CameraController.OnEvent(event);
}
