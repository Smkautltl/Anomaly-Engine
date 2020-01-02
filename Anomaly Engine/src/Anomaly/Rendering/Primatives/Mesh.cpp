#include "aepch.h"
#include "Mesh.h"
#include "Anomaly/Rendering/Renderer.h"

namespace Anomaly
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures)
		:m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
	{
		setupMesh();
	}

	void Mesh::Draw(std::shared_ptr<Shader> shader)
	{
		unsigned int diffuseN = 1;
		unsigned int specularN = 1;
		unsigned int normalN = 1;
		unsigned int heightN = 1;

		for(auto i = 0; i < m_Textures.size(); i++)
		{
			shader->SetActiveTexture(i);

			std::string num;
			std::string name = m_Textures[i].type;

			if(name == "material.texture_diffuse")
				num = std::to_string(diffuseN++);
			else if(name == "material.texture_specular")
				num = std::to_string(specularN++);
			else if(name == "material.texture_normal")
				num = std::to_string(normalN++);
			else if(name == "material.texture_height")
				num = std::to_string(heightN++);

			shader->SetUniformInt(name + num, i);
			shader->BindTexture(m_Textures[i].id);
		}
		
		m_VertexArray->Bind();
		Renderer::Submission(m_VertexArray, shader);
		m_VertexArray->UnBind();
		shader->SetActiveTexture(0);
	}

	void Mesh::setupMesh()
	{

		m_VertexArray.reset(VertexArray::Create());
		m_VertexBuffer.reset(VertexBuffer::Create(&m_Vertices[0] , m_Vertices.size() * sizeof(Vertex)));
		BufferLayout layout =
		{
			{Anomaly::ShaderDataType::Vec3, "a_Position"},
			{Anomaly::ShaderDataType::Vec3, "a_Normal"},
			{Anomaly::ShaderDataType::Vec2, "a_TexCoords"},
			{Anomaly::ShaderDataType::Vec3, "a_Tangent"},
			{Anomaly::ShaderDataType::Vec3, "a_BiTangent"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_IndexBuffer.reset(IndexBuffer::Create(&m_Indices[0], m_Indices.size()));
		m_VertexArray->AddIndexBuffer(m_IndexBuffer);

		m_VertexArray->UnBind();
	}
}