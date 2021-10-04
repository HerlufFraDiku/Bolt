#include "EditorLayer.h"
#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

namespace Bolt {
	EditorLayer::EditorLayer() :
		Layer("Bolt Editor"),
		m_CameraController(1280.0f / 720.0f),
		m_FPSCounter() {
        FramebufferSpec framebufferSpec;
        framebufferSpec.Width = 1280;
        framebufferSpec.Height = 720;
        m_Framebuffer = Framebuffer::Create(framebufferSpec);

        m_ActiveScene = CreateRef<Scene>();
        m_Square = m_ActiveScene->CreateEntity("Square");
        m_Square.Add<SpriteRenderer>();
    }

	void EditorLayer::OnUpdate(Timestep dt) {
		m_FPSCounter.OnUpdate(dt);
        if (m_ViewportFocused) m_CameraController.OnUpdate(dt);
        
        m_Framebuffer->Bind();
		RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();

		Renderer2D::ResetStats();
		Renderer2D::BeginScene(m_CameraController.GetCamera());

		float n = 5.0f;
		float s = 0.5f;
		float o = 0.05f;
		for (float x = -n; x < n; x += s) {
			for (float y = -n; y < n; y += s) {
				glm::vec4 color = glm::vec4((x + n) / (2.0f * n), 0.4f, (y + n) / (2.0f * n), 1.0f);
				Renderer2D::DrawQuad(
					Quad(glm::vec2(x, y), glm::vec2(s - o), color)
				);
			}
		}

        m_ActiveScene->OnUpdate(dt);

		Renderer2D::EndScene();
        m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender() {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else { dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode; }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
        if (!opt_padding) ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
        if (!opt_padding) ImGui::PopStyleVar();
        if (opt_fullscreen) ImGui::PopStyleVar(2);
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Options")) {
                if (ImGui::MenuItem("Exit")) Application::Get().Close();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Begin("Stats");
        ImGui::Text("%.1f FPS (%.1f ms)", m_FPSCounter.FPS(), m_FPSCounter.FrameTime());
        auto Stats = Renderer2D::GetStats();
        ImGui::Text("RenderStats");
        ImGui::Text("Drawcalls:\t%d", Stats.DrawCount);
        ImGui::Text("Quads:\t%d", Stats.QuadCount);

        ImGui::Separator();
        ImGui::Text("%s", m_Square.tag().c_str());
        auto& squareColor = m_Square.Get<SpriteRenderer>().Color;
        ImGui::ColorEdit4("Square color", glm::value_ptr(squareColor));
        ImGui::Separator();

        ImGui::End();

        RenderViewport();

        ImGui::End();
	}

    void EditorLayer::RenderViewport() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");

        m_ViewportHovered = ImGui::IsWindowHovered();
        m_ViewportFocused = ImGui::IsWindowFocused();
        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize)) {
            m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
            m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

            m_CameraController.Resize(m_ViewportSize.x / m_ViewportSize.y);
        }

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererId();
        ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();

    }

	void EditorLayer::OnEvent(Event& event) {
        m_CameraController.OnEvent(event);
	}
}