#include "Sandbox2D.hpp"
#include "Engine/Hydrogen.hpp"
#include "Engine/EntryPoint.hpp"

class SandboxApplication
	: public Hydrogen::Application
{
public:
	SandboxApplication()
	{
		PushLayer(new Sandbox2D{});
	}
};

Hydrogen::Application* Hydrogen::CreateApplication()
{
	return new SandboxApplication{};
}