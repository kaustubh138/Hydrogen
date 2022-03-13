#include "Hydrogen/Hydrogen.hpp"

class Sandbox
	: public Hydrogen::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Hydrogen::Application* Hydrogen::CreateApplication()
{
	return new Sandbox{};
}