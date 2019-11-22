#include <Anomaly.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class ExampleLayer : public Anomaly::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-3.2f, 3.2f, -1.8f, 1.8f, -5.f, 5.f)
	{	
		float VerticesAndColour[3 * 7] =
		{
		//	  X		 Y		Z		 R		 G		 B		 A
			-0.5f, -0.5f,  0.0f,	1.0f,	0.05f,	0.05f,	1.0f,
			 0.5f, -0.5f,  0.0f,	0.05f,	1.0f,	0.05f,	1.0f,
			 0.0f,  0.5f,  0.0f,	0.05f,	0.05f,	1.0f,	1.0f
		};
		uint32_t indices[3] =
		{
			0,1,2
		};
		//This sets up the layout of the Vertex Buffer
		Anomaly::BufferLayout layout = 
		{
				{Anomaly::ShaderDataType::Vec3, "a_Position"},
				{Anomaly::ShaderDataType::Vec4, "a_Colour"}
		};
		
		//Sets up all the buffers and arrays needed for rendering		
		m_VertexArray.reset(Anomaly::VertexArray::Create());

		std::shared_ptr<Anomaly::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<Anomaly::IndexBuffer> m_IndexBuffer;
		
		m_VertexBuffer.reset(Anomaly::VertexBuffer::Create(VerticesAndColour, sizeof(VerticesAndColour)));
		m_VertexBuffer->SetLayout(layout);		
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		
		m_IndexBuffer.reset(Anomaly::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)) );
		m_VertexArray->AddIndexBuffer(m_IndexBuffer);
		//-------------------------------------------------------

		m_Shader.reset(new Anomaly::Shader("Triangle.vs", "Triangle.fs"));

//Temporary for testing----------------------------------------------------------------------------
		{
			float SquareVertices[3 * 4] =
			{
		//	  X		 Y		Z
			-1.0f, -1.0f,  0.0f,
			 1.0f, -1.0f,  0.0f,
			 1.0f,  1.0f,  0.0f,
			-1.0f,  1.0f,  0.0f,
		};
			uint32_t SquareIndices[6] =
			{
			0,1,2,
			2,3,0,
		};
			Anomaly::BufferLayout layout2 = 
			{
				{Anomaly::ShaderDataType::Vec3, "a_Position"},
		};
			
			m_SquareVertexArray.reset(Anomaly::VertexArray::Create());
			
			std::shared_ptr<Anomaly::VertexBuffer> m_SquareVertexBuffer;
			m_SquareVertexBuffer.reset(Anomaly::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
			m_SquareVertexBuffer->SetLayout(layout2);
			m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);
			
			std::shared_ptr<Anomaly::IndexBuffer> m_SquareIndexBuffer;
			m_SquareIndexBuffer.reset(Anomaly::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t) ));
			m_SquareVertexArray->AddIndexBuffer(m_SquareIndexBuffer);		

			m_Shader2.reset(new Anomaly::Shader( "Square.vs", "Square.fs"));			
		}
//-------------------------------------------------------------------------------------------------
	}

	void OnUpdate(Anomaly::TimeStep deltaTime) override
	{
		
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
		m_Camera.SetRotation(m_CamRot);
			
		Anomaly::Renderer::BeginScene(m_Camera);
		{
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			y += 100;
			x += 100;
				
			glm::vec3 pos = glm::vec3(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			AE_CORE_INFO("{0}", glm::to_string(transform));
			Anomaly::Renderer::Submission(m_SquareVertexArray, m_Shader2, transform);
			Anomaly::Renderer::Submission(m_VertexArray, m_Shader);
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
	
	Anomaly::OrthoCamera m_Camera;
	glm::vec3 m_CamPos = {0.f, 0.f, 0.f};
	float m_CamRot = 0.f;
	float m_CameraSpeed = 3.0f;

	glm::vec3 squartransfrom = glm::vec3(0.f);
	int x = 0;
	int y = 0;
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