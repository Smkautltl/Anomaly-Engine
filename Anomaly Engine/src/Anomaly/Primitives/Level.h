#pragma once
#include "Object.h"

namespace Anomaly
{

	class Level
	{
	public:
		Level(std::string name, std::string path);
		Level();
		~Level();

		void AddObject();
		bool RemoveObject();

		void LoadLevel(std::string name, std::string path);
		void SaveLevel();

	private:

		std::string m_Name;
		std::string m_Path;
		std::vector<Object> m_Objects;

		glm::vec3 m_CamPos;
	};
	
}
