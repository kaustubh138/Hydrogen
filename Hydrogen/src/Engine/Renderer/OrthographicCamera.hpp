#pragma once

#include "glm/glm.hpp"

namespace Hydrogen
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

	public:
		// Getter Setter for Position
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		const glm::vec3& GetPosition() { return m_Position; }

		// Getter Setter for Rotation
		void SetRotation(const glm::float32& rotation_degrees) { m_Rotation = rotation_degrees; RecalculateViewMatrix(); }
		const glm::float32& GetRotation() { return m_Rotation; }

		void SetProjection(float left, float right, float bottom, float top);

		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

	private: 
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix; // Cache for ViewMatrix * ProjectionMatrix 

		glm::vec3 m_Position{0.0f, 0.0f, 0.0f};
		glm::float32 m_Rotation{ 0.0f };
	};
}

