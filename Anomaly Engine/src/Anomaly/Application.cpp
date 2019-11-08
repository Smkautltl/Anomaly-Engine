#include "aepch.h"
#include "Application.h"
#include "Log.h"

#include <glad/glad.h>

#include "Anomaly/input.h"

namespace Anomaly
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	//This creates a new window
	Application::Application()
	{
		AE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		
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
		BufferLayout layout = 
		{
				{ShaderDataType::Vec3, "a_Position"},
				{ShaderDataType::Vec4, "a_Colour"}
		};

		//Sets up all the buffers and arrays needed for rendering
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		
		m_VertexArray.reset(VertexArray::Create());
		
		m_VertexBuffer.reset( VertexBuffer::Create(VerticesAndColour, sizeof(VerticesAndColour)));
		m_VertexBuffer->SetLayout(layout);		
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		
		m_IndexBuffer.reset( IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)) );
		m_VertexArray->AddIndexBuffer(m_IndexBuffer);

		const std::string VertexSrc = 
			R"(
				#version 330 core

				layout(location = 0)in vec3 a_Position;
				layout(location = 1)in vec4 a_Colour;
				

				out vec3 v_Position;
				out vec4 v_Colour;
		
				void  main()
				{
					gl_Position = vec4(a_Position, 1.0);
					v_Position = a_Position;
					v_Colour = a_Colour;
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
		m_Shader.reset(new Shader(VertexSrc, FragmentSrc));

//Temporary for testing----------------------------------------------------------------------------
		float SquareVertices[3 * 4] =
		{
		//	  X		 Y		Z
			-0.8f, -0.8f,  0.0f,
			 0.8f, -0.8f,  0.0f,
			 0.8f,  0.8f,  0.0f,
			-0.8f,  0.8f,  0.0f
		};
		uint32_t SquareIndices[6] =
		{
			0,1,2,
			2,3,0
		};
		BufferLayout layout2 = 
		{
				{ShaderDataType::Vec3, "a_Position"},
		};
		
		m_SquareVertexArray.reset(VertexArray::Create());
		
		std::shared_ptr<VertexBuffer> m_SquareVertexBuffer;
		m_SquareVertexBuffer.reset(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		m_SquareVertexBuffer->SetLayout(layout2);
		m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);
		
		std::shared_ptr<IndexBuffer> m_SquareIndexBuffer;
		m_SquareIndexBuffer.reset(IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t) ));
		m_SquareVertexArray->AddIndexBuffer(m_SquareIndexBuffer);
		
		const std::string VertexSrc2 = 
			R"(
				#version 330 core

				layout(location = 0)in vec3 a_Position;			

				out vec3 v_Position;
		
				void  main()
				{
					gl_Position = vec4(a_Position, 1.0);
					v_Position = a_Position;
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
		
		m_Shader2.reset(new Shader(VertexSrc2, FragmentSrc2));
//-------------------------------------------------------------------------------------------------
		
	}

	Application::~Application() = default;

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* Overlay)
	{
		m_LayerStack.PushOverlay(Overlay);
		Overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.05, 0.05, 0.05, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader2->Bind();
			m_SquareVertexArray->Bind();
			auto SquareIndexBuffers = m_SquareVertexArray->GetIndexBuffers();
			for (const auto& IndexBuffer : SquareIndexBuffers)
			{
				glDrawElements(GL_TRIANGLES, IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			}
						
			m_Shader->Bind();
			m_VertexArray->Bind();
			auto IndexBuffers = m_VertexArray->GetIndexBuffers();
			for (const auto& IndexBuffer : IndexBuffers)
			{
				glDrawElements(GL_TRIANGLES, IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			}
			
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
