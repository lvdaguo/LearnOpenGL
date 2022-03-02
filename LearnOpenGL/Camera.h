#pragma once

#include <glm/glm.hpp>

const float MinFov = 1.0f, MaxFov = 80.0f;
const float MinPitch = -90.0f, MaxPitch = 90.0f;
const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& up,
		float moveSpeed = 0.01f, float mouseSensitivity = 0.1f, float fov = 45.0f,
		float near = 0.1f, float far = 50.0f);
	~Camera();

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewProjectionMatrix() const;
	void Update();

private:
	void RemoveInputCallback();
	void SetInputCallback();

public:
	glm::vec3 GetPosition() const { return m_position; }
	glm::vec3 GetFront() const { return m_front; }

private:
	glm::vec3 m_position;
	glm::vec3 m_up, m_front, m_right;
	
    float m_yaw, m_pitch;

    float m_fov, m_aspect;
	float m_near, m_far;

	float m_moveSpeed;
	float m_mouseSensitivity;

	class Action2<float, float> m_mouseOffsetCallback;
	class Action2<float, float> m_mouseScrollCallback;

	void SetMovement(const class Input& inputModule);
	void SetDirection(float xOffset, float yOffset);
	void SetZoom(float xOffset, float yOffset);
	void UpdateFacing();
};

