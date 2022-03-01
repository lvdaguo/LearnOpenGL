#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <functional>

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
class InputModule
{
public:
	InputModule(const class Window& window);
	~InputModule();

	void SetMouseEnabled(bool enabled) const;

	bool GetKeyDown(enum class Key key) const
	{
		return glfwGetKey(m_windowPointer, static_cast<int>(key)) == GLFW_PRESS;
	}

	glm::vec2 GetMousePosition() const { return m_mousePosition; }
	//glm::vec2 GetMouseOffset() const { 
	//	// need fix
	//	auto t = m_mouseOffset;
	//	m_mouseOffset = glm::vec2();
	//	return t; 
	//}
	//glm::vec2 GetMouseScroll() const {
	//	auto t = m_mouseScroll;
	//	m_mouseScroll = glm::vec2();
	//	return t; 
	//}

	static void AddMouseOffsetCallback(std::function<void(float, float)> callback)
	{
		m_mouseOffsetCallback.push_back(callback);
	}

	static void AddMouseScrollCallback(std::function<void(float, float)> callback)
	{
		m_mouseScrollCallback.push_back(callback);
	}

private:
	GLFWwindow* m_windowPointer;

	static void MouseCallback(GLFWwindow* window, double x, double y);
	static void ScrollCallback(GLFWwindow* window, double x, double y);

	static std::vector<std::function<void(float, float)>> m_mouseOffsetCallback;
	static std::vector<std::function<void(float, float)>> m_mouseScrollCallback;

	static glm::vec2 m_screenCenter;
	static glm::vec2 m_mousePosition;
};

