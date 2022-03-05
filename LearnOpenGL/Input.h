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
/// 输入单例
/// </summary>
class Input : public Singleton<Input>
{
public:
	Input() = default;
	~Input() = default;
	void Init();

	/// <summary> 显示鼠标，隐藏鼠标 </summary>
	void SetMouseEnabled(bool enabled) const;

	/// <summary> 检测按键输入 </summary>
	bool GetKeyDown(enum class Key key) const
	{
		return glfwGetKey(GetWindowPointer(), static_cast<int>(key)) == GLFW_PRESS;
	}

	/// <summary> 获取鼠标当前的屏幕坐标（像素位置） </summary>
	glm::vec2 GetMousePosition() const { return m_mousePosition; }

	/// <summary> 获取鼠标位置偏移事件 </summary>
	static class Event2<float, float>& GetMouseOffsetEvent() { return m_mouseOffsetEvent; }
	
	/// <summary> 获取鼠标滚轮偏移事件 </summary>
	static class Event2<float, float>& GetMouseScrollEvent() { return m_mouseScrollEvent; }

private:
	// 使用Window单例中的GLFWwindow指针
	// 设置GLFW中的鼠标事件回调（必须是非成员函数）
	static void MouseCallback(GLFWwindow* window, double x, double y);
	static void ScrollCallback(GLFWwindow* window, double x, double y);

	static class Event2<float, float> m_mouseOffsetEvent;
	static class Event2<float, float> m_mouseScrollEvent;

	static glm::vec2 m_screenCenter;
	static glm::vec2 m_mousePosition;
};

