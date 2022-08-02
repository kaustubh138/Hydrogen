#include "pch.hpp"
#include "LayerStack.hpp"

namespace Hydrogen
{
	LayerStack::LayerStack()
	{
		m_Layers.emplace_back(new Layer{});
	}

	LayerStack::~LayerStack()
	{
		for (Layer* l : m_Layers)
			delete l;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIdx, layer);
		m_LayerInsertIdx++;
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIdx--;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}	
}