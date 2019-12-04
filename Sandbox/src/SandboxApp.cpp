#include <Anomaly.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Anomaly::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(45.f,1280.f, 720.f)
	{		
		float Vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		
		//This sets up the layout of the Vertex Buffer
		Anomaly::BufferLayout layout = 
		{
				{Anomaly::ShaderDataType::Vec3, "a_Position"},
				{Anomaly::ShaderDataType::Vec2, "a_TexCoords0"}
		};
		
		//Sets up all the buffers and arrays needed for rendering		
		m_VertexArray.reset(Anomaly::VertexArray::Create());

		std::shared_ptr<Anomaly::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<Anomaly::IndexBuffer> m_IndexBuffer;
		
		m_VertexBuffer.reset(Anomaly::VertexBuffer::Create(Vertices, sizeof(Vertices)));
		m_VertexBuffer->SetLayout(layout);		
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		
		//m_IndexBuffer.reset(Anomaly::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)) );
		//m_VertexArray->AddIndexBuffer(m_IndexBuffer);
		//-------------------------------------------------------

		m_Shader.reset(new Anomaly::Shader("Triangle.vs", "Triangle.fs"));
		m_Shader->GenerateTextures();
		
	}

	void OnUpdate(Anomaly::TimeStep deltaTime) override
	{
		glm::vec3 cubePositions[] = {
			glm::vec3( 2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3( 2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3( 1.3f, -2.0f, -2.5f),
			glm::vec3( 1.5f,  2.0f, -2.5f),
			glm::vec3( 1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		
		if(Anomaly::Input::IsKeyPressed(AE_KEY_W))
		{
			m_CamPos.y += m_CameraSpeed * deltaTime;
		}
		else if(Anomaly::Input::IsKeyPressed(AE_KEY_S))
		{
			m_CamPos.y -= m_CameraSpeed * deltaTime;
		}
		
		if(Anomaly::Input::IsKeyPressed(AE_KEY_A))
		{
			m_CamPos.x -= m_CameraSpeed * deltaTime;
		}
		else if(Anomaly::Input::IsKeyPressed(AE_KEY_D))
		{
			m_CamPos.x += m_CameraSpeed * deltaTime;
		}
				
		if(Anomaly::Input::IsKeyPressed(AE_KEY_LEFT))
		{
			m_CamRot += (m_CameraSpeed * 10) * deltaTime;
		}
		else if(Anomaly::Input::IsKeyPressed(AE_KEY_RIGHT))
		{
			m_CamRot -= (m_CameraSpeed * 10) * deltaTime;
		}
		
		Anomaly::RenderRequest::SetClearColour(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		Anomaly::RenderRequest::Clear();

		m_Camera.SetPosition(m_CamPos);
		//m_Camera.SetRotation(m_CamRot);

		m_Camera.RecalcuteProjMatrix(45.f,1280.f, 720.f);
		m_Camera.RecalcuteViewMatrix();
		m_Shader->SetUniformMatrix4("u_ViewMatrix",  m_Camera.GetViewMatrix());
		m_Shader->SetUniformMatrix4("u_ProjMatrix",  m_Camera.GetProjMatrix());

		Anomaly::Renderer::BeginScene(m_Camera);
		{
			m_Shader->BindTextures();
			
			for (auto i = 0; i < 10; i++)
			{
				glm::mat4 modelmatrix = glm::mat4(1.f);
				modelmatrix = glm::translate(modelmatrix, cubePositions[i]);
				float angle = 20.f * i;
				modelmatrix = glm::rotate(modelmatrix, glm::radians(angle), glm::vec3(1.0f,0.3f,0.5f));
				//modelmatrix = glm::rotate(modelmatrix, ((float)deltaTime.GetMilliSecs() / 2.f) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
				m_Shader->SetUniformMatrix4("u_ModelMatrix", modelmatrix);

				Anomaly::Renderer::Submission(m_VertexArray, m_Shader);
			}	
			
		}
		Anomaly::Renderer::EndScene();
		//ImGui::GetWindowDrawList()->AddImage();
	}

	void OnImGuiRender() override
	{
		
	}
	
	void OnEvent(Anomaly::Event& event) override
	{
	}
	
private:
	std::shared_ptr<Anomaly::VertexArray> m_VertexArray;
	std::shared_ptr<Anomaly::Shader> m_Shader;
	
	std::shared_ptr<Anomaly::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Anomaly::Shader> m_Shader2;
	
	Anomaly::PerspecCamera m_Camera;
	glm::vec3 m_CamPos = {0.f, 0.f, 0.f};
	float m_CamRot = 0.f;
	float m_CameraSpeed = 3.0f;
		
};

class Sandbox final : public Anomaly::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox()
	= default;
};

Anomaly::Application* Anomaly::CreateApplication()
{
	return new Sandbox;
}