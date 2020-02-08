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

	class PerspecCamera
	{
	public:
		PerspecCamera(float FOV, float width, float height, float nearValue = 0.1f, float farValue = 100.0f);

		const glm::mat4& GetProjMatrix() const { return m_ProjMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }

		const void SetProjMatrix(const glm::mat4& matrix) { m_ProjMatrix= matrix; }
		const void SetViewMatrix(const glm::mat4& matrix) { m_ViewMatrix= matrix; }
		const void SetModelMatrix(const glm::mat4& matrix){ m_ModelMatrix= matrix; }

		const glm::vec3& GetCameraFront() const { return m_CamFront; }
		const glm::vec3& GetCameraUp() const { return m_CamUp; }
		const glm::vec3& GetCameraPos() const { return m_CamPos; }
		

		void RecalculateViewMatrix();
		void RecalculateProjMatrix(float FOV, float width, float height, float nearValue = 0.1f, float farValue = 100.0f);
		void RecalculateCameraRotation();

		void SetPosition(const glm::vec3& cameraposition) {m_CamPos = cameraposition; RecalculateViewMatrix(); }
		void SetYaw(const float& yaw) {m_Yaw += yaw * m_Sensitvity; RecalculateCameraRotation(); }
		void SetPitch(const float& pitch) {m_Pitch += pitch * m_Sensitvity; RecalculateCameraRotation(); }
		
	private:
		glm::mat4 m_ProjMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ModelMatrix;
										    
		glm::vec3 m_CamPos;
		glm::vec3 m_CamUp;
		glm::vec3 m_CamFront;
		
		glm::vec3 m_CamRotation =	{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraTarget =	{ 0.0f, 0.0f, 0.0f };
		
		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;
		float m_Sensitvity = 0.05f;

	};
}