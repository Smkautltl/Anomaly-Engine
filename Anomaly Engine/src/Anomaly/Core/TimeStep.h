#pragma once

namespace Anomaly
{
	class TimeStep
	{
	public:
		TimeStep(float time)
			:m_Time(time)
		{
		}

		operator float() const { return m_Time; } 
		
		float GetSecs() const { return m_Time; };
		float GetMilliSecs() const { return m_Time * 1000.f; }
		
		void SetglfwTime(const float glfwTime) { m_glfwTime = glfwTime; }
		const float GetglfwTime() const { return m_glfwTime; }		
	private:
		float m_Time;
		float m_glfwTime;
	};
}