#include <Anomaly.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>


class ExampleLayer : public Anomaly::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(45.f,1280.f, 720.f), NanoSuit(Anomaly::Model("Models\\Nanosuit\\nanosuit.obj"))
	{
		
		LastX = Anomaly::Input::GetMouseX();
		LastY = Anomaly::Input::GetMouseY();

		m_Shader.reset(new Anomaly::Shader("ModelLoading.vs", "ModelLoading.fs"));
		m_Shader->GenerateTextures();
		
		m_CamPos =	{0.f, 0.f, 3.0f};

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

		Anomaly::Renderer::BeginScene(m_Camera);
		{
			Anomaly::RenderRequest::SetClearColour(glm::vec4(0.5f, 0.0f, 0.5f, 1.0f));
			Anomaly::RenderRequest::Clear();
			
			//Renders the Nanosuit model
			{
				m_Shader->Bind();				
				
				m_Shader->SetUniformMatrix4("u_ProjMatrix", m_Camera.GetProjMatrix());
				m_Shader->SetUniformMatrix4("u_ViewMatrix", m_Camera.GetViewMatrix());

				// render the loaded model
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
				model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
				m_Shader->SetUniformMatrix4("u_ModelMatrix", model);
				
				Anomaly::Renderer::Submission(NanoSuit, m_Shader);
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
	Anomaly::Model NanoSuit;
	
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