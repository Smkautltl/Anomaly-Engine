#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"
#include "VertexArray.h"

namespace Anomaly
{

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;		
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		void Draw(std::shared_ptr<Shader> shader);
		
	public:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<Texture> m_Textures;

	private:
		void setupMesh();

	private:
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};
	
}
