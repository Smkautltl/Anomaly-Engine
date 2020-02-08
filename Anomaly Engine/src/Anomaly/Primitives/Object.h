#pragma once
#include "Anomaly/Rendering/Primatives/Shader.h"
#include "Anomaly/Rendering/Primatives/Model.h"
#include "Anomaly/Rendering/Primatives/Light.h"

namespace Anomaly
{

	enum ObjectType
	{
		None = 0,
		ModelType = 1,
		InstancedModelType = 2,
		LightType = 3
	};
	
	class Object
	{
	public:
		Object(Model model, std::shared_ptr<Shader> shader);
		Object(Model model, std::shared_ptr<Shader> shader, int instances);
		Object(Light model, std::shared_ptr<Shader> shader);
		~Object();

		void DrawCall();

	private:
		
		Model m_Model;
		Light m_Light;
		std::shared_ptr<Shader> m_Shader;
		ObjectType m_Type;
		int m_Instances;

		glm::vec3 m_Pos;
		glm::vec3 m_Rot;
		glm::vec3 m_Scale;

	};
}
