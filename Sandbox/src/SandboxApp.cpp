#include <Anomaly.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/include/GLFW/glfw3.h"

class ExampleLayer : public Anomaly::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(45.f,1280.f, 720.f)
	{
		LastX = Anomaly::Input::GetMouseX();
		LastY = Anomaly::Input::GetMouseY();

		//Cubes Objects----------------------------------------------------------------------------------
		float Vertices[] = {
			// positions           // normals            // texture coords
			-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
								   						 
			-0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,    0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,    1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,    1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,    1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,    0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,    0.0f, 0.0f,
								   						 
			-0.5f,  0.5f,  0.5f, - 1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, - 1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, - 1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, - 1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, - 1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, - 1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
								   						 
			 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
								   						 
			-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
								   						 
			-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f

		};	
		//This sets up the layout of the Vertex Buffer
		Anomaly::BufferLayout layout = 
		{
				{Anomaly::ShaderDataType::Vec3, "a_Position"},
				{Anomaly::ShaderDataType::Vec3, "a_Normal"},
				{Anomaly::ShaderDataType::Vec2, "a_TexCoords"}
		};
		
		//Sets up all the buffers and arrays needed for rendering		
		m_VertexArray.reset(Anomaly::VertexArray::Create());

		std::shared_ptr<Anomaly::VertexBuffer> m_VertexBuffer;		
		m_VertexBuffer.reset(Anomaly::VertexBuffer::Create(Vertices, sizeof(Vertices)));
		m_VertexBuffer->SetLayout(layout);		
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		
		m_Shader.reset(new Anomaly::Shader("Light.vs", "Light.fs"));
		m_Shader->GenerateTextures();
		//-----------------------------------------------------------------------------------------------

		//Light Object--------------------------------------------------------------------------------------------
		m_LightVertexArray.reset(Anomaly::VertexArray::Create());	
		m_LightVertexArray->AddVertexBuffer(m_VertexBuffer);
		m_LightShader.reset(new Anomaly::Shader("LightCube.vs", "LightCube.fs"));
		//---------------------------------------------------------------------------------------------------------
		
		m_CamPos =	{0.f, 0.f, 3.0f};
		
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

		if(Anomaly::Input::IsKeyPressed(AE_KEY_ESCAPE))
			Anomaly::Application::m_Running = false;
		
		float m_CameraSpeed = 3.0f * deltaTime;
		if(Anomaly::Input::IsKeyPressed(AE_KEY_W))
		{
			m_CamPos += m_CameraSpeed * m_Camera.GetCameraFront();
		}
		else if(Anomaly::Input::IsKeyPressed(AE_KEY_S))
		{
			m_CamPos -= m_CameraSpeed * m_Camera.GetCameraFront();
		}
		
		if(Anomaly::Input::IsKeyPressed(AE_KEY_A))
		{
			m_CamPos -= glm::normalize(glm::cross(m_Camera.GetCameraFront(), m_Camera.GetCameraUp())) * m_CameraSpeed;
		}
		else if(Anomaly::Input::IsKeyPressed(AE_KEY_D))
		{
			m_CamPos += glm::normalize(glm::cross(m_Camera.GetCameraFront(), m_Camera.GetCameraUp())) * m_CameraSpeed;
		}
				
		if(Anomaly::Input::IsKeyPressed(AE_KEY_LEFT))
		{
			m_CamRot += (m_CameraSpeed * 10) * deltaTime;
		}
		else if(Anomaly::Input::IsKeyPressed(AE_KEY_RIGHT))
		{
			m_CamRot -= (m_CameraSpeed * 10) * deltaTime;
		}

		if(Anomaly::Input::IsMouseButtonPressed(AE_MOUSE_BUTTON_MIDDLE))
		{
			float xOffset = Anomaly::Input::GetMouseX() - LastX;
			float yOffset = LastY - Anomaly::Input::GetMouseY();

			m_Camera.SetPitch(yOffset);
			m_Camera.SetYaw(xOffset);
			
			LastX = Anomaly::Input::GetMouseX(); 
			LastY = Anomaly::Input::GetMouseY();
		}
		
		LastX = Anomaly::Input::GetMouseX(); 
		LastY = Anomaly::Input::GetMouseY();
		
		Anomaly::RenderRequest::SetClearColour(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		Anomaly::RenderRequest::Clear();

		m_Camera.SetPosition(m_CamPos);

		m_Camera.RecalcuteProjMatrix(45.f,1280.f, 720.f);
		
		glm::vec3 lightpos(1.2f, 1.0f, 2.0f);

		Anomaly::Renderer::BeginScene(m_Camera);
		{
			m_Shader->Bind();
			m_Shader->SetUniformMatrix4("u_ViewMatrix",  m_Camera.GetViewMatrix());
			m_Shader->SetUniformMatrix4("u_ProjMatrix",  m_Camera.GetProjMatrix());

			//Object inputs
			m_Shader->SetUniformVec3("v_ObjectColour", glm::vec3(1.0f,0.0f,0.31f));
			m_Shader->SetUniformVec3("v_LightColour",  glm::vec3(1.0f, 1.0f, 1.0f));	
			m_Shader->SetUniformVec3("v_LightPos",  lightpos);	
			m_Shader->SetUniformVec3("v_CamPos",  m_Camera.GetCameraPos());
			m_Shader->SetUniformFloat("time", deltaTime.GetglfwTime());

			//Material Settings
			m_Shader->SetUniformVec3("m_material.ambient",  glm::vec3(0.174f, 0.011f, 0.011f));
			m_Shader->SetUniformVec3("m_material.specular", glm::vec3(0.727f, 0.626f, 0.626f));
			m_Shader->SetUniformFloat("m_material.shininess", 6.0f);

			//Light Settings
			m_Shader->SetUniformVec3("l_Light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
			m_Shader->SetUniformVec3("l_Light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
			m_Shader->SetUniformVec3("l_Light.specular",glm::vec3(1.0f, 1.0f, 1.0f));

			m_Shader->BindTextures();
			
			for (auto i = 0; i < 10; i++)
			{
				m_Camera.SetModelMatrix(glm::mat4(1.f));
				m_Camera.SetModelMatrix(glm::translate(m_Camera.GetModelMatrix(), cubePositions[i]));
				float angle = 25.f * i;
				m_Camera.SetModelMatrix(glm::rotate(m_Camera.GetModelMatrix(), glm::radians(angle), glm::vec3(1.0f,0.3f,0.5f)));
				m_Shader->SetUniformMatrix4("u_ModelMatrix", m_Camera.GetModelMatrix());

				Anomaly::Renderer::Submission(m_VertexArray, m_Shader);
			}

			m_LightShader->Bind();
			m_LightShader->SetUniformMatrix4("u_ViewMatrix",  m_Camera.GetViewMatrix());
			m_LightShader->SetUniformMatrix4("u_ProjMatrix",  m_Camera.GetProjMatrix());
			
			m_Camera.SetModelMatrix(glm::mat4(1.f));
			m_Camera.SetModelMatrix(glm::translate(m_Camera.GetModelMatrix(), lightpos));
			m_Camera.SetModelMatrix(glm::scale(m_Camera.GetModelMatrix(), glm::vec3(1.f)));
			m_LightShader->SetUniformMatrix4("u_ModelMatrix", m_Camera.GetModelMatrix());
			
			Anomaly::Renderer::Submission(m_LightVertexArray, m_LightShader);
			
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
	std::shared_ptr<Anomaly::VertexArray> m_LightVertexArray;
	std::shared_ptr<Anomaly::Shader> m_LightShader;
	
	Anomaly::PerspecCamera m_Camera;
	glm::vec3 m_CamPos =	{0.f, 0.f, 3.0f};
	float m_CamRot = 0.f;
	float LastX, LastY;
		
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