#include "Hydrogen/Hydrogen.hpp"
#include "Hydrogen/Layers/Layer.hpp"

#include "ImGui/ImGuiLayer.hpp"

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

	}

	void OnEvent(Hydrogen::Events::Event& e) override
	{

	}
};

class Sandbox
	: public Hydrogen::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new Hydrogen::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Hydrogen::Application* Hydrogen::CreateApplication()
{
	return new Sandbox{};
}