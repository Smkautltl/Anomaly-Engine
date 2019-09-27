#include "aepch.h"
#include "LayerStack.h"

namespace Anomaly
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (auto layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		const auto iteration = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (iteration != m_Layers.end())
		{
			m_Layers.erase(iteration);
			--m_LayerInsert;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		const auto iteration = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (iteration != m_Layers.end())
			m_Layers.erase(iteration);
	}
}
