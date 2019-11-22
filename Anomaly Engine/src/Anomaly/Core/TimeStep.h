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
		
		
	private:
		float m_Time;
	};
}