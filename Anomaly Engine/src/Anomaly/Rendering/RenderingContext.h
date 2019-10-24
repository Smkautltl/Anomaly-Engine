#pragma once


namespace Anomaly
{
	class RenderingContext
	{
	public:
		virtual void Init() = 0;
		virtual void Swapbuffers() = 0;
	};
	
}