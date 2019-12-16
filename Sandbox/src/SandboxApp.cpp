#include <Anomaly.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>


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

		//Light Object--------------------------------------------------------------------------------------------
		std::shared_ptr<Anomaly::VertexBuffer> m_VertexBuffer;		
		m_VertexBuffer.reset(Anomaly::VertexBuffer::Create(Vertices, sizeof(Vertices)));
		m_VertexBuffer->SetLayout(layout);		

		m_LightVertexArray.reset(Anomaly::VertexArray::Create());	
		m_LightVertexArray->AddVertexBuffer(m_VertexBuffer);
		m_LightShader.reset(new Anomaly::Shader("LightCube.vs", "LightCube.fs"));
		//---------------------------------------------------------------------------------------------------------
		
		m_CamPos =	{0.f, 0.f, 3.0f};

		//Loads in nanosuit model
		{
			std::string AppPath = __argv[0];	
			AppPath.replace(AppPath.end() - 11, AppPath.end(), "Models\\Nanosuit\\nanosuit.obj");
			const char* Path = AppPath.c_str();
			Anomaly::Model NanoSuit = Anomaly::Model(Path);
		}
	}

	void OnUpdate(Anomaly::TimeStep deltaTime) override
	{
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
		m_Camera.SetPosition(m_CamPos);
		m_Camera.RecalcuteProjMatrix(45.f,1280.f, 720.f);
		
		Anomaly::RenderRequest::SetClearColour(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Anomaly::RenderRequest::Clear();

		Anomaly::Renderer::BeginScene(m_Camera);
		{

			glm::vec3 pointLightPositions[] = 
			{
				glm::vec3( 0.7f,  0.2f,  2.0f),
				glm::vec3( 2.3f, -3.3f, -4.0f),
				glm::vec3(-4.0f,  2.0f, -12.0f),
				glm::vec3( 0.0f,  0.0f, -3.0f)
			};

			for (auto i = 0; i < 4; i++)
			{
				m_LightShader->Bind();
				m_LightShader->SetUniformMatrix4("u_ViewMatrix",  m_Camera.GetViewMatrix());
				m_LightShader->SetUniformMatrix4("u_ProjMatrix",  m_Camera.GetProjMatrix());
				
				m_Camera.SetModelMatrix(glm::mat4(1.f));
				m_Camera.SetModelMatrix(glm::translate(m_Camera.GetModelMatrix(), pointLightPositions[i]));
				m_Camera.SetModelMatrix(glm::scale(m_Camera.GetModelMatrix(), glm::vec3(0.1f)));
				m_LightShader->SetUniformMatrix4("u_ModelMatrix", m_Camera.GetModelMatrix());
				
				Anomaly::Renderer::Submission(m_LightVertexArray, m_LightShader);
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