#pragma once
#include "Engine/Hydrogen.hpp"

class ExampleLayer
	: public Hydrogen::Layer
{
private:
	std::shared_ptr<Hydrogen::VertexArray> m_VertexArray;
	std::shared_ptr<Hydrogen::Shader> m_Shader;

	Hydrogen::OrthographicCamera m_OrthoCamera;

public:
	ExampleLayer();

	void OnUpdate() override;

	void OnEvent(Hydrogen::Events::Event& e) override;
};

class Sandbox
	: public Hydrogen::Application
{
public:
	Sandbox();
	~Sandbox();
};
