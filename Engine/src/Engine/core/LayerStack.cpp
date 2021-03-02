#include "engpch.h"

#include "LayerStack.h"

namespace Engine
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}


	void LayerStack::PushLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_layerInsertIdx, layer);
		layer->OnAttach();
		m_layerInsertIdx++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
		overlay->OnAttach();
	}


	void LayerStack::PopLayer(Layer* layer)
	{
		std::vector<Layer*>::iterator it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIdx, layer);
		if (it != m_layers.begin() + m_layerInsertIdx)
		{
			layer->OnDetach();
			m_layers.erase(it);
			m_layerInsertIdx--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		std::vector<Layer*>::iterator it = std::find(m_layers.begin() + m_layerInsertIdx, m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			overlay->OnDetach();
			m_layers.erase(it);
		}
	}

}