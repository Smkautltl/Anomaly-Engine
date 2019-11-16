#include "aepch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Anomaly
{
	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float nearZ, float farZ)
		: m_ProjMatrix(glm::ortho(left, right, bottom, top, nearZ, farZ)), m_ViewMatrix(1.0f)
	{
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}

	void OrthoCamera::RecalcuateViewProjMatrix()
	{
		//Adds the cameras position to the transform
		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), m_CamPos) * glm::rotate(glm::mat4(1.0f), glm::radians(m_CamRotationZ), glm::vec3(0, 0, 1));
		//Adds the cameras rotation to the transform
		//Transform = glm::rotate(Transform, glm::radians(m_CamRotationZ), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(Transform);
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}
}
