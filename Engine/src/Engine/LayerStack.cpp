#include "engpch.h"

#include "LayerStack.h"

namespace Engine
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		// perform check to make sure the layer is still in the vector
		// if we pop a layer we lose the reference to it so the layer wont be deleted
		// maybe use an enable/disable switch in place of pop
		for (Layer* layer : m_layers)
		{
			delete layer;
		}
	}


	void LayerStack::pushLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_layerInsertIdx, layer);
		m_layerInsertIdx++;
	}

	void LayerStack::pushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
	}


	void LayerStack::popLayer(Layer* layer)
	{
		std::vector<Layer*>::iterator it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			m_layerInsertIdx--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay)
	{
		std::vector<Layer*>::iterator it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
		}
	}

}