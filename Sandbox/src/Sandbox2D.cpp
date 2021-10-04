#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D() :
	Bolt::Layer("Sandbox2D"),
	m_CameraController(1280.0f / 720.0f),
	m_FPSCounter(),
	m_CheckerTex(Bolt::Texture2D::Create("assets/textures/checkerboard.png")),
	m_QuadColor(glm::vec4(0.3f, 0.3f, 0.8f, 1.0f))
{}

void Sandbox2D::OnUpdate(Bolt::Timestep dt) {
	m_CameraController.OnUpdate(dt);
	m_FPSCounter.OnUpdate(dt);

	Bolt::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Bolt::RenderCommand::Clear();

	Bolt::Renderer2D::ResetStats();
	Bolt::Renderer2D::BeginScene(m_CameraController.GetCamera());

	float n = 5.0f;
	float s = 0.5f;
	float o = 0.05f;
	for (float x = -n; x < n; x += s) {
		for (float y = -n; y < n; y += s) {
			glm::vec4 color = glm::vec4((x + n) / (2.0f * n), 0.4f, (y + n) / (2.0f * n), 1.0f);
			Bolt::Renderer2D::DrawQuad(
				Bolt::Quad(glm::vec2(x, y), glm::vec2(s - o), color)
			);
		}
	}

	Bolt::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Controls");
    ImGui::Text("%.1f FPS (%.1f ms)", m_FPSCounter.FPS(), m_FPSCounter.FrameTime());

    auto Stats = Bolt::Renderer2D::GetStats();
    ImGui::Text("RenderStats");
    ImGui::Text("Drawcalls:\t%d", Stats.DrawCount);
    ImGui::Text("Quads:\t%d", Stats.QuadCount);

    ImGui::End();
}

void Sandbox2D::OnEvent(Bolt::Event& event) {
	m_CameraController.OnEvent(event);
}
