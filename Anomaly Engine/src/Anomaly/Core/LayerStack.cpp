#include "aepch.h"
#include "LayerStack.h"

namespace Anomaly
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (auto layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		const auto iteration = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (iteration != m_Layers.end())
		{
			m_Layers.erase(iteration);
			m_LayerInsertIndex--;
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
