#include "Hydrogen/Hydrogen.hpp"
#include "Hydrogen/Layers/Layer.hpp"

class ExampleLayer
	: public Hydrogen::Layer
{
public:
	ExampleLayer()
		: Hydrogen::Layer("Example")
	{

	}

	void OnUpdate() override
	{
		H2_INFO("Layer Update");
	}

	void OnEvent(Hydrogen::Event::Event& e) override
	{
		H2_INFO("Event {0}" , e);
	}
};

class Sandbox
	: public Hydrogen::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Hydrogen::Application* Hydrogen::CreateApplication()
{
	return new Sandbox{};
}