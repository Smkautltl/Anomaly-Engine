#include <Anomaly.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Anomaly::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_frameBuffer(Anomaly::FrameBuffer::Create()), m_Camera(45.f,1280.f, 720.f), NanoSuit(Anomaly::Model("Content\\Models\\Nanosuit\\nanosuit.obj")), Sphere(Anomaly::Model("Content\\Models\\Sphere\\Sphere.obj"))
	{
		//Sets the Last X & Y to the current mouse pos upon starting the application
		LastX = Anomaly::Input::GetMouseX();
		LastY = Anomaly::Input::GetMouseY();

		//Resests the variable and creates the new shader
		m_Shader.reset(new Anomaly::Shader("ModelLoading.vs", "ModelLoading.fs"));
		m_LightShader.reset(new Anomaly::Shader("LightCube.vs", "LightCube.fs"));

		//Sets the cam position to 3 units
		m_CamPos =	{0.f, 0.f, 3.0f};
		
	}

	void OnUpdate(Anomaly::TimeStep deltaTime) override
	{
		m_frameBuffer->Bind();
		
		glm::vec3 pointLightPositions[] = 
		{
			glm::vec3( 0.7f,  0.2f,  2.0f),
			glm::vec3( 2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3( 0.0f,  0.0f, -3.0f)
		};

		//Set shaders uniforms
		{
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
		}

		//Exits application if escape button is pressed
		if(Anomaly::Input::IsKeyPressed(AE_KEY_ESCAPE))
			Anomaly::Application::m_Running = false;

		//Sets the camrea speed with a delta Time offset as fps shouldn't affect camera movement
		float m_CameraSpeed = 3.0f * deltaTime;

		//W and S keys move the camera forward and backwards
		if(Anomaly::Input::IsKeyPressed(AE_KEY_W))
		{
			m_CamPos += m_CameraSpeed * m_Camera.GetCameraFront();
		}
		else if(Anomaly::Input::IsKeyPressed(AE_KEY_S))
		{
			m_CamPos -= m_CameraSpeed * m_Camera.GetCameraFront();
		}

		//A and S keys moves the camera left and right
		if(Anomaly::Input::IsKeyPressed(AE_KEY_A))
		{
			m_CamPos -= glm::normalize(glm::cross(m_Camera.GetCameraFront(), m_Camera.GetCameraUp())) * m_CameraSpeed;
		}
		else if(Anomaly::Input::IsKeyPressed(AE_KEY_D))
		{
			m_CamPos += glm::normalize(glm::cross(m_Camera.GetCameraFront(), m_Camera.GetCameraUp())) * m_CameraSpeed;
		}

		//If the middle mouse button is pressed then it will start rotating the camera
		if(Anomaly::Input::IsMouseButtonPressed(AE_MOUSE_BUTTON_MIDDLE))
		{
			float xOffset = Anomaly::Input::GetMouseX() - LastX;
			float yOffset = LastY - Anomaly::Input::GetMouseY();

			m_Camera.SetPitch(yOffset);
			m_Camera.SetYaw(xOffset);
			
			LastX = Anomaly::Input::GetMouseX(); 
			LastY = Anomaly::Input::GetMouseY();
		}

		//Sets the last X and Y to the current mouse position
		LastX = Anomaly::Input::GetMouseX(); 
		LastY = Anomaly::Input::GetMouseY();

		//Sets the cameras position after the alterations that happened above
		m_Camera.SetPosition(m_CamPos);
		//Recalcuates the projection matrix with the ImGUI window width and height 
		m_Camera.RecalculateProjMatrix(45.f, WindowWidth, WindowHeight);

		//Sets the lastTime and frames to 0 for the ImGUI window
		if(!FPSSetup)
		{
			lastTime = deltaTime.GetglfwTime(); 
			Frames = 0;
			
			FPSSetup = true;
		}

		//Sets a local variable to the glfwTime so that ImGui can use it
		glfwTime = deltaTime.GetglfwTime();

		//Sets up the scene by accepting the camera object
		Anomaly::Renderer::BeginScene(m_Camera);
		{
			//Sets the clear colour to a bright magenta colour and clears the screen
			Anomaly::RenderRequest::SetClearColour(glm::vec4(0.5f, 0.0f, 0.5f, 1.0f));
			Anomaly::RenderRequest::Clear();

			//Loops and draws a light to the screen with given light positions
			for (unsigned int i = 0; i < 4; i++)
			{
				m_LightShader->Bind();
				m_LightShader->SetUniformMatrix4("u_ProjMatrix", -m_Camera.GetProjMatrix());
				m_LightShader->SetUniformMatrix4("u_ViewMatrix", -m_Camera.GetViewMatrix());
				
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, pointLightPositions[i]);
				model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
				m_LightShader->SetUniformMatrix4("u_ModelMatrix", model);
				
				Anomaly::Renderer::Submission(Sphere, m_LightShader);
			}
			
			//Renders the Nanosuit model at given position
			{
				m_Shader->Bind();				
				
				m_Shader->SetUniformMatrix4("u_ProjMatrix", m_Camera.GetProjMatrix());
				m_Shader->SetUniformMatrix4("u_ViewMatrix", m_Camera.GetViewMatrix());
				m_Shader->SetUniformVec3("v_camPos", m_Camera.GetCameraPos());

				// render the loaded model
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
				model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	// it's a bit too big for our scene, so scale it down
				m_Shader->SetUniformMatrix4("u_ModelMatrix", model);
				
				Anomaly::Renderer::Submission(NanoSuit, m_Shader);
			}
		}
		Anomaly::Renderer::EndScene();
		m_frameBuffer->UnBind();
	}

	void OnImGuiRender() override
	{
		
		ImGui::DockSpaceOverViewport();
	//FPS Window-----------------------------------------------
		ImGui::Begin("FPS");		
		double currentTime = glfwTime;
		Frames++;
		if(currentTime - lastTime > 1.0)
		{
			FPS = Frames;
			Frames = 0;
			lastTime = currentTime;
		}
		ImGui::Text("FPS: %i", FPS);		
		ImGui::Text("Average Frame Time: %f", 1000.0/FPS);		
		ImGui::End();
	//----------------------------------------------------------
		
		//Content Window
		ImGui::Begin("Content");
		ImGui::Text("Content Implementation coming soon");
		ImGui::End();
		//Properties Window
		ImGui::Begin("Properties");
		ImGui::Text("Properties Implementation coming soon");	
		ImGui::ColorEdit3("Test Colour Edit", test);
		ImGui::Dummy(ImVec2(0,0));
		ImGui::End();
		//World Settings Window
		ImGui::Begin("World Settings");
		ImGui::Text("World Settings Implementation coming soon");
		ImGui::End();

	//Renderer Window-------------------------------------------------------------------------------------------
		ImGui::Begin("Renderer");
		WindowWidth = ImGui::GetWindowWidth();
		WindowHeight = ImGui::GetWindowHeight();	
		ImGui::GetWindowDrawList()->AddImage( reinterpret_cast<void*>(m_frameBuffer->ReturnFrameBuffer(WindowWidth, WindowHeight)),
										 ImVec2(ImGui::GetCursorScreenPos()), 
										 ImVec2(ImGui::GetCursorScreenPos().x + WindowWidth, ImGui::GetCursorScreenPos().y + WindowHeight), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
	//----------------------------------------------------------------------------------------------------------
		
	}
	
	void OnEvent(Anomaly::Event& event) override
	{

	}
	
private:
	//Shader Variables
	std::shared_ptr<Anomaly::VertexArray> m_VertexArray;
	std::shared_ptr<Anomaly::Shader> m_Shader;
	std::shared_ptr<Anomaly::Shader> m_LightShader;
	bool LightingCompiled = false;

	//Camera Variables
	Anomaly::PerspecCamera m_Camera;
	glm::vec3 m_CamPos =	{0.f, 0.f, 3.0f};
	float m_CamRot = 0.f;
	float LastX, LastY;

	//FPS Variables
	bool FPSSetup = false;
	int Frames{};
	double lastTime{};
	double glfwTime{};
	int FPS{};

	//FrameBuffer
	std::shared_ptr<Anomaly::FrameBuffer> m_frameBuffer;
	float WindowWidth = 1600;
	float WindowHeight = 900;

	//ImGui Test Variables
	float test[3] = {0,0,0};

	//Model Variables
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