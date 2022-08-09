#include "Engine/Hydrogen.hpp"
#include "Engine/Layers/Layer.hpp"

#include "Engine/ImGui/ImGuiLayer.hpp"

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
		if (Hydrogen::Input::IsKeyPressed(H2_KEY_TAB))
			H2_TRACE("Tab Pressed");
	}

	void OnEvent(Hydrogen::Events::Event& e) override
	{
		if (e.GetEventType() == Hydrogen::Events::EventType::KeyPressed)
		{
			Hydrogen::Events::KeyPressed& key_event = static_cast<Hydrogen::Events::KeyPressed&>(e);
			if (key_event.GetKeyCode() == H2_KEY_TAB)
				H2_TRACE("Tab Key Pressed");
			H2_TRACE("{0}", (char)key_event.GetKeyCode());
		}
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