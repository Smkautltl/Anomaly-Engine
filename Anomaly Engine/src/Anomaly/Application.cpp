#include "aepch.h"
#include "Application.h"
#include "Log.h"

#include <glad/glad.h>

#include "Anomaly/input.h"

namespace Anomaly
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	static GLenum ShaderDataType_To_GLenum(ShaderDataType Type)
	{
		switch (Type)
		{
			case ShaderDataType::Vec:	return GL_FLOAT;
			case ShaderDataType::Vec2:	return GL_FLOAT;
			case ShaderDataType::Vec3:	return GL_FLOAT;
			case ShaderDataType::Vec4:	return GL_FLOAT;
			
			case ShaderDataType::Mat3:	return GL_FLOAT;
			case ShaderDataType::Mat4:	return GL_FLOAT;
			
			case ShaderDataType::Int: 	return GL_INT;
			case ShaderDataType::Int2:	return GL_INT;
			case ShaderDataType::Int3:	return GL_INT;
			case ShaderDataType::Int4:	return GL_INT;
			
			case ShaderDataType::Bool:	return GL_BOOL;
		}

		AE_CORE_ASSERT(false, "Unknown shader data type!")
		return 0;
	}
	
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

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		
		float Vertices[3 * 7] =
		{
		//	  X		 Y		Z		 R		 G		 B		 A
			-0.5f, -0.5f,  0.0f,	1.0f,	0.05f,	0.05f,	1.0f,
			 0.5f, -0.5f,  0.0f,	0.05f,	1.0f,	0.05f,	1.0f,
			 0.0f,  0.5f,  0.0f,	0.05f,	0.05f,	1.0f,	1.0f
		};

		m_VertexBuffer.reset( VertexBuffer::Create(Vertices, sizeof(Vertices)));
		
		{
			BufferLayout layout = 
			{
				{ShaderDataType::Vec3, "a_Position"},
				{ShaderDataType::Vec4, "a_Colour"}
			};

			m_VertexBuffer->SetLayout(layout);
		}
		
		uint32_t i = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, 
								  element.GetComponentCount(), 
								  ShaderDataType_To_GLenum(element.Type), 
								  element.Normalized ? GL_TRUE : GL_FALSE, 
								  layout.GetStride(), 
								  reinterpret_cast<const void*>(element.Offset)
								 );
			i++;
		}
		
		uint32_t indices[3] =
		{
			0,1,2
		};
		
		m_IndexBuffer.reset( IndexBuffer::Create(indices, sizeof(indices)/ sizeof(uint32_t)) );

		std::string VertexSrc = 
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

		std::string FragmentSrc = 
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
		
		
	}

	Application::~Application()
	= default;

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

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			
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
