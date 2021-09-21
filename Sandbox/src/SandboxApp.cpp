#include <Bolt.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

float verticies[4 * 5] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
};

uint32_t indicies[6] = { 0, 1, 2, 2, 3, 0 };

class ExampleLayer : public Bolt::Layer {
private:
	Bolt::Ref<Bolt::VertexArray> m_VA;
	Bolt::Ref<Bolt::Shader> m_Shader;
	Bolt::Ref<Bolt::Texture2D> m_CheckerTex, m_HectorTex;
	Bolt::OrthographicCamera m_Camera;

public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) 
	{
		// Load assets
		m_Shader = Bolt::Shader::Create("assets/shaders/TextureShader.glsl");
		m_CheckerTex = Bolt::Texture2D::Create("assets/textures/checkerboard.png");
		m_HectorTex = Bolt::Texture2D::Create("assets/textures/hector-large.png");

		// Create vertex buffer to hold verticies and describe the attribute layout so the shader can use them
		Bolt::Ref<Bolt::VertexBuffer> VB = Bolt::VertexBuffer::Create(verticies, sizeof(verticies));
		VB->SetLayout({
			{ Bolt::ShaderElementType::Float3, "a_Position" },
			{ Bolt::ShaderElementType::Float2, "a_TexCoord" }
		});

		// Create index buffer to tell renderer which verticies to draw
		Bolt::Ref<Bolt::IndexBuffer> IB = Bolt::IndexBuffer::Create(indicies, 6);

		// Create vertex array to hold vertex and index buffers
		m_VA = Bolt::VertexArray::Create();
		m_VA->AddVertexBuffer(VB);
		m_VA->SetIndexBuffer(IB);
	}

	void OnUpdate(Bolt::Timestep dt) override {
		glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));

		Bolt::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Bolt::RenderCommand::Clear();

		Bolt::Renderer::BeginScene(m_Camera);

		m_Shader->Bind();
		std::dynamic_pointer_cast<Bolt::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);
		m_CheckerTex->Bind(0);
		Bolt::Renderer::Submit(m_Shader, m_VA, transform);
		m_HectorTex->Bind(0);
		Bolt::Renderer::Submit(m_Shader, m_VA, transform);

		Bolt::Renderer::EndScene();
	}
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