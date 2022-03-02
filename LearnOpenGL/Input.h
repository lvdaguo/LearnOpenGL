#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Singleton.h"
#include "Window.h"
#include "Event.h"

/// <summary>
/// 按键枚举
/// </summary>
enum class Key
{
	Escape = GLFW_KEY_ESCAPE,
	W = GLFW_KEY_W,
	A = GLFW_KEY_A,
	S = GLFW_KEY_S,
	D = GLFW_KEY_D
};

/// <summary>
/// 管理输入
/// </summary>
class Input : public Singleton<Input>
{
public:
	Input();
	~Input();
	void Init();

	void SetMouseEnabled(bool enabled) const;

	bool GetKeyDown(enum class Key key) const
	{
		return glfwGetKey(GetWindowPointer(), static_cast<int>(key)) == GLFW_PRESS;
	}

	glm::vec2 GetMousePosition() const { return m_mousePosition; }

	static class Event2<float, float>& GetMouseOffsetEvent() { return m_mouseOffsetEvent; }
	static class Event2<float, float>& GetMouseScrollEvent() { return m_mouseScrollEvent; }

private:
	static void MouseCallback(GLFWwindow* window, double x, double y);
	static void ScrollCallback(GLFWwindow* window, double x, double y);

	static class Event2<float, float> m_mouseOffsetEvent;
	static class Event2<float, float> m_mouseScrollEvent;

	static glm::vec2 m_screenCenter;
	static glm::vec2 m_mousePosition;
};

