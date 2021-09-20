#include <Bolt.h>
#include "imgui/imgui.h"

std::string vertexSrc = R"(
			#version 330 core
			
			uniform mat4 u_ViewProjection;

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main() {
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				v_Color = a_Color;
			}
		)";

std::string fragmentSrc = R"(
			#version 330 core
			
			in vec3 v_Position;
			in vec4 v_Color;

			layout(location = 0) out vec4 o_Color;

			void main() {
				o_Color = v_Color;
			}
		)";

float verticies[3 * 7] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

uint32_t indicies[3] = { 0, 1, 2 };

class ExampleLayer : public Bolt::Layer {
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
		// Create Shader
		m_Shader.reset(Bolt::Shader::Create(vertexSrc, fragmentSrc));

		// Create vertex buffer to hold verticies
		std::shared_ptr<Bolt::VertexBuffer> VB;
		VB.reset(Bolt::VertexBuffer::Create(verticies, sizeof(verticies)));

		// Describe the layout of each element so the shader can use them
		VB->SetLayout({
			{ Bolt::ShaderElementType::Float3, "a_Position" },
			{ Bolt::ShaderElementType::Float4, "a_Color" }
		});

		// Create index buffer to tell renderer which verticies to draw
		std::shared_ptr<Bolt::IndexBuffer> IB;
		IB.reset(Bolt::IndexBuffer::Create(indicies, 3));

		// Create vertex array to hold vertex and index buffers
		m_VA.reset(Bolt::VertexArray::Create());
		m_VA->AddVertexBuffer(VB);
		m_VA->SetIndexBuffer(IB);
	}

	void OnUpdate() override {
		MoveCamera();

		Bolt::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Bolt::RenderCommand::Clear();

		// Draw triangle
		Bolt::Renderer::BeginScene(m_Camera);
		m_Shader->Bind();
		Bolt::Renderer::Submit(m_Shader, m_VA);
		Bolt::Renderer::EndScene();
	}

	void MoveCamera() {
		glm::vec3 translation = glm::vec3(0.0f);
		float rotation = 0.0f;

		if (Bolt::Input::IsKeyPressed(Bolt::Key::W)) translation.y += -0.1f;
		if (Bolt::Input::IsKeyPressed(Bolt::Key::A)) translation.x +=  0.1f;
		if (Bolt::Input::IsKeyPressed(Bolt::Key::S)) translation.y +=  0.1f;
		if (Bolt::Input::IsKeyPressed(Bolt::Key::D)) translation.x += -0.1f;
		if (Bolt::Input::IsKeyPressed(Bolt::Key::Space)) rotation +=   5.0f;

		m_Camera.SetPosition(m_Camera.GetPosition() + translation);
		m_Camera.SetRotation(m_Camera.GetRotation() + rotation);
	}

private:
	std::shared_ptr<Bolt::VertexArray> m_VA;
	std::shared_ptr<Bolt::Shader> m_Shader;
	Bolt::OrthographicCamera m_Camera;
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