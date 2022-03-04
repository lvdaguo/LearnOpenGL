#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Input.h"
#include "Helper.h"
#include "Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& up,
	float moveSpeed, float mouseSensitivity, float fov,
	float near, float far) :
	m_position(position), m_up(up),
	m_front(0.0f, 0.0f, -1.0f), m_yaw(-90.0f), m_pitch(0.0f),
	m_moveSpeed(moveSpeed), m_mouseSensitivity(mouseSensitivity), m_fov(fov),
	m_near(near), m_far(far)
{
	m_aspect = Window::GetInstance().GetAspect();
	UpdateFacing();
	SetInputCallback();
}

Camera::~Camera() { }

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(m_fov, m_aspect, m_near, m_far);
}

glm::mat4 Camera::GetViewProjectionMatrix() const
{
	return GetProjectionMatrix() * GetViewMatrix();
}

void Camera::SetInputCallback()
{
	m_mouseOffsetCallback = Action2<float, float>([this](float xOffset, float yOffset)
		{
			SetDirection(xOffset, yOffset);
		});
	Input::GetInstance().GetMouseOffsetEvent().Add(m_mouseOffsetCallback);

	m_mouseScrollCallback = Action2<float, float>([this](float xOffset, float yOffset)
		{
			SetZoom(xOffset, yOffset);
		});
	Input::GetInstance().GetMouseScrollEvent().Add(m_mouseScrollCallback);
}

void Camera::RemoveInputCallback()
{
	Input::GetInstance().GetMouseOffsetEvent().Remove(m_mouseOffsetCallback);
	Input::GetInstance().GetMouseScrollEvent().Remove(m_mouseScrollCallback);
}

#include <iostream>

void Camera::Update()
{
	SetMovement(Input::GetInstance());
	// m_yaw += 1.0f * m_mouseSensitivity * Helper::GetDeltaTime();
	std::cout << m_yaw << std::endl;
}

void Camera::SetMovement(const Input& input)
{
	glm::vec2 dir = glm::vec2(0.0f, 0.0f);
	if (input.GetKeyDown(Key::A)) dir.x -= 1.0f;
	else if (input.GetKeyDown(Key::D)) dir.x += 1.0f;
	else if (input.GetKeyDown(Key::W)) dir.y += 1.0f;
	else if (input.GetKeyDown(Key::S)) dir.y -= 1.0f;
	else return;

	float velocity = m_moveSpeed * Helper::GetDeltaTime();

	dir = glm::normalize(dir);
	m_position += dir.y * m_front * velocity;
	m_position += dir.x * m_right * velocity;
}

void Camera::SetDirection(float xOffset, float yOffset)
{
	m_yaw += xOffset * m_mouseSensitivity * Helper::GetDeltaTime();
	m_pitch += yOffset * m_mouseSensitivity * Helper::GetDeltaTime();
	m_pitch = glm::clamp(m_pitch, MinPitch, MaxPitch);
	UpdateFacing();
}

void Camera::SetZoom(float xOffset, float yOffset)
{
	float scrollY = yOffset * Helper::GetDeltaTime();
	m_fov = glm::clamp(m_fov - scrollY, MinFov, MaxFov);
}

void Camera::UpdateFacing()
{
	float x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	float y = sin(glm::radians(m_pitch));
	float z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(glm::vec3(x, y, z));

	m_right = glm::normalize(glm::cross(m_front, WorldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}
