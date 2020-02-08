#include "aepch.h"
#include "Object.h"

namespace Anomaly
{
	Object::Object(Model model, std::shared_ptr<Shader> shader)
		: m_Model(model), m_Shader(shader)
	{
		m_Type = ObjectType::ModelType;
	}

	Object::Object(Model model, std::shared_ptr<Shader> shader, int instances)
		:m_Model(model), m_Shader(shader), m_Instances(instances)
	{
		m_Type = ObjectType::InstancedModelType;
	}

	Object::Object(Light light, std::shared_ptr<Shader> shader)
		:m_Light(light), m_Shader(shader), m_Model(nullptr)
	{
		m_Type = ObjectType::LightType;
	}

	Object::~Object()
	{
		
	}

	void Object::DrawCall()
	{
		switch (m_Type)
		{
		case None:
			AE_CORE_ERROR("No object type has been selected!");
			break;
			
		case ModelType:
			m_Model.Draw(m_Shader);
			break;
			
		case InstancedModelType:
			//m_Model.Draw(m_Shader, m_Instances);
			break;
			
		case LightType:
			//m_Light.DrawCall(m_Shader);
			break;
			
		default: ;
		}
		
	}
}
