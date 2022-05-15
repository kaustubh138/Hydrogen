#pragma once

#include  "Core.hpp"
#include "Layer.hpp"

namespace Hydrogen
{
	class H2_API LayerStack
	{
	private:
		std::vector<Layer*> m_Layers; // Contains all the layer including the overlay layer at the front()
		std::vector<Layer*>::iterator m_LayerInsert; // Pointer to position before the overlay layer

	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
	
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);
	
		std::vector<Layer*>::iterator end() { return m_Layers.end(); };
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); };
	};
}