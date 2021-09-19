#include <Bolt.h>
#include "imgui/imgui.h"

std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				gl_Position = vec4(a_Position, 1.0);
				v_Position = a_Position;
				v_Color = a_Color;
			}
		)";

std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_Color;
			in vec3 v_Position;
			in vec4 v_Color;

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
	ExampleLayer() : Layer("Example") {
		// Create Shader
		m_Shader.reset(Bolt::Shader::Create(vertexSrc, fragmentSrc));

		// Create vertex buffer to hold verticies
		std::shared_ptr<Bolt::VertexBuffer> VB;
		VB.reset(Bolt::VertexBuffer::Create(verticies, sizeof(verticies)));

		// Describe the layout of each elements so shader can use them
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
		Bolt::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Bolt::RenderCommand::Clear();

		// Draw triangle
		Bolt::Renderer::BeginScene();
		m_Shader->Bind();
		Bolt::Renderer::Submit(m_VA);
		Bolt::Renderer::EndScene();
	}

private:
	std::shared_ptr<Bolt::VertexArray> m_VA;
	std::shared_ptr<Bolt::Shader> m_Shader;
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