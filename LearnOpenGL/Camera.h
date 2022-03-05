#pragma once

#include <glm/glm.hpp>

// 边界限制
const float MinFov = 1.0f, MaxFov = 80.0f;
const float MinPitch = -90.0f, MaxPitch = 90.0f;

// 默认值
const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
const float MoveSpeed = 0.1f;
const float MouseSensitivity = 0.1f;
const float Fov = 45.0f;
const float Near = 0.1f;
const float Far = 50.0f;
const glm::vec3 Front = glm::vec3(0.0f, 0.0f, 1.0f);
const float Yaw = -90.0f;
const float Pitch = 0.0f;

/// <summary>
/// 摄像机
/// </summary>
class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& up, float moveSpeed = MoveSpeed, 
		float mouseSensitivity = MouseSensitivity, float fov = Fov,
		float near = Near, float far = Far, const glm::vec3& front = Front, 
		float yaw = Yaw, float pitch = Pitch);
	~Camera();

	// 获取视图矩阵、投影矩阵、或者其组合
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewProjectionMatrix() const;

	/// <summary> 每帧调用 </summary>
	void Update();

private:
	// 订阅和取消订阅Input单例中的鼠标回调事件
	void SetInputCallback();
	void RemoveInputCallback();

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

	/// <summary> 鼠标位置偏移的回调函数 </summary>
	class Action2<float, float> m_mouseOffsetCallback;

	/// <summary> 鼠标滚轮滚动的回调函数 </summary>
	class Action2<float, float> m_mouseScrollCallback;

	void UpdateMovement(const class Input& inputModule);
	void OnMouseMove(float xOffset, float yOffset);
	void OnMouseScroll(float xOffset, float yOffset);

	/// <summary> 重新各个朝向 </summary>
	void UpdateFacing();
};

