#pragma once
#include "Engine/Hydrogen.hpp"

class ExampleLayer
	: public Hydrogen::Layer
{
public:
	ExampleLayer();

	void OnUpdate(Hydrogen::Timestep ts) override;

	void OnEvent(Hydrogen::Events::Event& e) override;

private:
	std::shared_ptr<Hydrogen::VertexArray> m_VertexArray;
	std::shared_ptr<Hydrogen::Shader> m_Shader;

	Hydrogen::OrthographicCamera m_OrthoCamera;
	glm::vec3 m_CameraPosition;
	glm::float32 m_CameraSpeed{0.1f};
};

class Sandbox
	: public Hydrogen::Application
{
public:
	Sandbox();
	~Sandbox();
};
