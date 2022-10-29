#pragma once
#include "Engine/Hydrogen.hpp"

class ExampleLayer
	: public Hydrogen::Layer
{
public:
	ExampleLayer();

	virtual void OnUpdate(Hydrogen::Timestep ts) override;
	virtual void OnEvent(Hydrogen::Events::Event& e) override;
	virtual void OnImGuiRender() override;

private:
	Hydrogen::Ref<Hydrogen::VertexArray> m_TriangleVA;
	Hydrogen::Ref<Hydrogen::Shader> m_TriangleShader;
	
	Hydrogen::Ref<Hydrogen::VertexArray> m_SquareVA;
	Hydrogen::Ref<Hydrogen::Shader> m_SquareShader;

	Hydrogen::OrthographicCamera m_OrthoCamera;
	glm::vec3 m_CameraPosition;
	glm::float32 m_CameraSpeed{0.5f};
	glm::vec4 m_SquareColor{ 0.2f, 0.3f, 0.8f, 0.0f };

private:
	void setupTraingle();
	void setupSqaure();
};

class Sandbox
	: public Hydrogen::Application
{
public:
	Sandbox();
	~Sandbox();
};
