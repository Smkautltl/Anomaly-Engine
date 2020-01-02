#include <Anomaly.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Anomaly::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(45.f,1280.f, 720.f), NanoSuit(Anomaly::Model("Content\\Models\\Nanosuit\\nanosuit.obj")), Sphere(Anomaly::Model("Content\\Models\\Sphere\\Sphere.obj"))
	{
		
		LastX = Anomaly::Input::GetMouseX();
		LastY = Anomaly::Input::GetMouseY();

		m_Shader.reset(new Anomaly::Shader("ModelLoading.vs", "ModelLoading.fs"));
		m_LightShader.reset(new Anomaly::Shader("LightCube.vs", "LightCube.fs"));
		
		m_CamPos =	{0.f, 0.f, 3.0f};

	}

	void OnUpdate(Anomaly::TimeStep deltaTime) override
	{
		glm::vec3 pointLightPositions[] = 
		{
			glm::vec3( 0.7f,  0.2f,  2.0f),
			glm::vec3( 2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3( 0.0f,  0.0f, -3.0f)
		};

		m_Shader->SetUniformFloat("material.shininess", 32.0f);
		
		//Directional light
		m_Shader->SetUniformVec3("dirLight.direction",	glm::vec3(-0.2f, -1.0f, -0.3f));
		m_Shader->SetUniformVec3("dirLight.ambient",	glm::vec3(0.05f, 0.05f, 0.05f));
		m_Shader->SetUniformVec3("dirLight.diffuse",	glm::vec3(0.4f, 0.4f, 0.4f));
		m_Shader->SetUniformVec3("dirLight.specular",	glm::vec3(0.5f, 0.5f, 0.5f));
		//Point light 1
		m_Shader->SetUniformVec3("pointLights[0].position", pointLightPositions[0]);
		m_Shader->SetUniformVec3("pointLights[0].ambient",	glm::vec3(0.05f, 0.05f, 0.05f));
		m_Shader->SetUniformVec3("pointLights[0].diffuse",	glm::vec3(0.8f, 0.8f, 0.8f));
		m_Shader->SetUniformVec3("pointLights[0].specular",glm::vec3(1.0f, 1.0f, 1.0f));
		m_Shader->SetUniformFloat("pointLights[0].constant", 1.0f);
		m_Shader->SetUniformFloat("pointLights[0].linear", 0.09);
		m_Shader->SetUniformFloat("pointLights[0].quadratic", 0.032);
		//Point light 2
		m_Shader->SetUniformVec3("pointLights[1].position", pointLightPositions[1]);
		m_Shader->SetUniformVec3("pointLights[1].ambient",	glm::vec3(0.05f, 0.05f, 0.05f));
		m_Shader->SetUniformVec3("pointLights[1].diffuse",	glm::vec3(0.8f, 0.8f, 0.8f));
		m_Shader->SetUniformVec3("pointLights[1].specular",glm::vec3(1.0f, 1.0f, 1.0f));
		m_Shader->SetUniformFloat("pointLights[1].constant", 1.0f);
		m_Shader->SetUniformFloat("pointLights[1].linear", 0.09);
		m_Shader->SetUniformFloat("pointLights[1].quadratic", 0.032);
		//Point light 3
		m_Shader->SetUniformVec3("pointLights[2].position", pointLightPositions[2]);
		m_Shader->SetUniformVec3("pointLights[2].ambient",	glm::vec3(0.05f, 0.05f, 0.05f));
		m_Shader->SetUniformVec3("pointLights[2].diffuse",	glm::vec3(0.8f, 0.8f, 0.8f));
		m_Shader->SetUniformVec3("pointLights[2].specular",glm::vec3(1.0f, 1.0f, 1.0f));
		m_Shader->SetUniformFloat("pointLights[2].constant", 1.0f);
		m_Shader->SetUniformFloat("pointLights[2].linear", 0.09);
		m_Shader->SetUniformFloat("pointLights[2].quadratic", 0.032);
		//Point light 4
		m_Shader->SetUniformVec3("pointLights[3].position", pointLightPositions[3]);
		m_Shader->SetUniformVec3("pointLights[3].ambient",	glm::vec3(0.05f, 0.05f, 0.05f));
		m_Shader->SetUniformVec3("pointLights[3].diffuse",	glm::vec3(0.8f, 0.8f, 0.8f));
		m_Shader->SetUniformVec3("pointLights[3].specular",glm::vec3(1.0f, 1.0f, 1.0f));
		m_Shader->SetUniformFloat("pointLights[3].constant", 1.0f);
		m_Shader->SetUniformFloat("pointLights[3].linear", 0.09);
		m_Shader->SetUniformFloat("pointLights[3].quadratic", 0.032);
			
		
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

			for (unsigned int i = 0; i < 4; i++)
			{
				m_LightShader->Bind();
				m_LightShader->SetUniformMatrix4("u_ProjMatrix", m_Camera.GetProjMatrix());
				m_LightShader->SetUniformMatrix4("u_ViewMatrix", m_Camera.GetViewMatrix());
				
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, pointLightPositions[i]);
				model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
				m_LightShader->SetUniformMatrix4("u_ModelMatrix", model);
				
				Anomaly::Renderer::Submission(Sphere, m_LightShader);
				
			}
			
			//Renders the Nanosuit model
			{
				m_Shader->Bind();				
				
				m_Shader->SetUniformMatrix4("u_ProjMatrix", m_Camera.GetProjMatrix());
				m_Shader->SetUniformMatrix4("u_ViewMatrix", m_Camera.GetViewMatrix());
				m_Shader->SetUniformVec3("v_camPos", m_Camera.GetCameraPos());

				// render the loaded model
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
				model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));	// it's a bit too big for our scene, so scale it down
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
	std::shared_ptr<Anomaly::Shader> m_LightShader;
	bool LightingCompiled = false;
	
	Anomaly::PerspecCamera m_Camera;
	glm::vec3 m_CamPos =	{0.f, 0.f, 3.0f};
	float m_CamRot = 0.f;
	float LastX, LastY;
	Anomaly::Model NanoSuit;
	Anomaly::Model Sphere;
	
	
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