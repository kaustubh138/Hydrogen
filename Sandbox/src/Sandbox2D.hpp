#pragma once

#include "Engine/Hydrogen.hpp"

class Sandbox2D
	: public Hydrogen::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hydrogen::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hydrogen::Event& e) override;

private:
	Hydrogen::OrthographicCameraController m_CameraController;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};