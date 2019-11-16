#pragma once

#include <glm/glm.hpp>

namespace Anomaly
{
	class OrthoCamera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float top, float nearZ = -1.0f, float farZ = 1.0f);

		void SetPosition(const glm::vec3& cameraposition) {m_CamPos = cameraposition; RecalcuateViewProjMatrix(); }
		void SetRotation(float camerarotationZ) {m_CamRotationZ = camerarotationZ; RecalcuateViewProjMatrix(); }

		const glm::vec3& GetCameraPosition() const { return m_CamPos; }
		float GetCameraRotationZ() const { return m_CamRotationZ; }

		const glm::mat4& GetProjMatrix() const { return m_ProjMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjMatrix() const { return m_ViewProjMatrix; }
		
	private:
		void RecalcuateViewProjMatrix();
		
	private:
		glm::mat4 m_ProjMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjMatrix;
		
		glm::vec3 m_CamPos = { 0.0f, 0.0f,0.0f };
		float m_CamRotationZ = 0.0f;
	};
}