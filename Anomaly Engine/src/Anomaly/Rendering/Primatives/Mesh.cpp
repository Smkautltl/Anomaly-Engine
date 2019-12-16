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

		for(auto i = 0; i < m_Textures.size(); i++)
		{
			shader->SetActiveTexture(i);

			std::string num;
			std::string name = m_Textures[i].type;

			if(name == "texture_diffuse")
				num = std::to_string(diffuseN++);
			else if(name == "texture_specular")
				num = std::to_string(specularN++);

			shader->SetUniformFloat(("material." + name+ num).c_str(), i);
			shader->BindTextures(m_Textures[i].id);
		}
		shader->SetActiveTexture(0);

		Renderer::Submission(m_VertexArray, shader);
	}

	void Mesh::setupMesh()
	{

		m_VertexArray.reset(VertexArray::Create());
		m_VertexBuffer.reset(VertexBuffer::Create(&m_Vertices[0] , m_Vertices.size() * sizeof(Vertex)));
		BufferLayout layout =
		{
			{Anomaly::ShaderDataType::Vec3, "a_Position"},
			{Anomaly::ShaderDataType::Vec3, "a_Normal"},
			{Anomaly::ShaderDataType::Vec2, "a_TexCoords"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_IndexBuffer.reset(IndexBuffer::Create(&m_Indices[0], m_Indices.size()));
		m_VertexArray->AddIndexBuffer(m_IndexBuffer);

		m_VertexArray->Bind();
	}
}
