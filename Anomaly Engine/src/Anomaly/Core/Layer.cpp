#include "aepch.h"
#include "Layer.h"
#include <utility>

namespace Anomaly
{
	Layer::Layer(std::string debugname)
		: m_DebugName(std::move(debugname))
	{
	}

	Layer::~Layer()
	= default;
}
