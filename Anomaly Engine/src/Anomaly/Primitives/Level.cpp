#include "aepch.h"
#include "Level.h"

namespace Anomaly
{
	Level::Level(std::string name, std::string path)
		: m_Name(name), m_Path(path)
	{
		
	}
	Level::Level()
	{
		
	}
	Level::~Level()
	= default;

	void Level::AddObject()
	{
		
	}
	bool Level::RemoveObject()
	{
		
		return false;
	}

	void Level::LoadLevel(std::string name, std::string path)
	{
		std::string AppPath = __argv[0];	
		AppPath.replace(AppPath.end() - 11, AppPath.end(), "Content\\" + path + name + ".level");
		m_Path = AppPath.c_str();

		std::ifstream LevelFile;
		std::stringstream LevelFileStream;
		LevelFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);	
		try
		{		
			LevelFile.open(m_Path);
			LevelFileStream << LevelFile.rdbuf();		
			LevelFile.close();
		}
		catch (std::ifstream::failure e)
		{
			AE_CORE_ERROR("Level File failed to read!: {0}", e.what());
		}

		for(std::string line; std::getline(LevelFileStream, line);)
		{
			if(line.find("#CAMPOS["))
			{			
				std::string camPos = line.substr(8, line.length() - 1);
			}
			else if(line.find("#MODEL["))
			{
				std::string modelPath = line.substr(8, line.length() - 1);
			}
			else if(line.find("#INSTMODEL["))
			{
				std::string instModelPath = line.substr(8, line.length() - 1);
			}
			else if(line.find("#LIGHT["))
			{
				std::string lightPath = line.substr(8, line.length() - 1);
			}
		}
	}
	void Level::SaveLevel()
	{
		
	}
}
