#include <Anomaly.h>
#include "imgui/imgui.h"

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
		
		const std::string VertexSrc = 
			R"(
				#version 330 core

				layout(location = 0)in vec3 a_Position;
				layout(location = 1)in vec4 a_Colour;

				uniform mat4 u_ViewProjMatrix;

				out vec3 v_Position;
				out vec4 v_Colour;
		
				void  main()
				{
					v_Position = a_Position;
					v_Colour = a_Colour;
					gl_Position = u_ViewProjMatrix * vec4(a_Position, 1.0);	
				}
			)";

		const std::string FragmentSrc = 
			R"(
				#version 330 core

				layout(location = 0) out vec4 o_Colour;
		
				in vec3 v_Position;
				in vec4 v_Colour;

				void  main()
				{
					o_Colour = vec4(v_Position * 0.5 + 0.5, 1.0);
					o_Colour = v_Colour;
				}
			)";	
		m_Shader.reset(new Anomaly::Shader(VertexSrc, FragmentSrc));

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
			
			const std::string VertexSrc2 = 
				R"(
					#version 330 core

					layout(location = 0)in vec3 a_Position;			
					uniform mat4 u_ViewProjMatrix;
			
					out vec3 v_Position;
			
					void  main()
					{			
						v_Position = a_Position;
						gl_Position = u_ViewProjMatrix * vec4(a_Position, 1.0);
					}
				)";

			const std::string FragmentSrc2 = 
				R"(
					#version 330 core

					layout(location = 0) out vec4 o_Colour;
			
					in vec3 v_Position;
					in vec4 v_Colour;

					void  main()
					{
						o_Colour = vec4(0.5, 0.5, 1.0);
					}
				)";
			
			m_Shader2.reset(new Anomaly::Shader(VertexSrc2, FragmentSrc2));
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
			Anomaly::Renderer::Submission(m_SquareVertexArray, m_Shader2);
			Anomaly::Renderer::Submission(m_VertexArray, m_Shader);
		}
		Anomaly::Renderer::EndScene();
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