#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include "Singleton.h"

/// <summary>
/// 窗口单例
/// </summary>
class Window : public Singleton<Window>
{
public:
	Window();
	~Window();
	void Init(unsigned int width, unsigned int height, const std::string& name);

private:
	// GLFW负责创建窗口，管理输入
	void InitGLFW();
	void CreateWindow(unsigned int width, unsigned int height, const std::string& name);
	// 设置GLFW的回调
	void SetupCallback();

public:
	GLFWwindow* GetWindowPointer() const { return m_windowPointer; }

	/// <summary> 获取屏幕宽度 </summary>
	unsigned int GetWidth() const { return m_width; }
	/// <summary> 获取屏幕高度 </summary>
	unsigned int GetHeight() const { return m_height; }
	/// <summary> 获取屏幕宽高比 </summary>
	float GetAspect() const { return static_cast<float>(m_width) / m_height; }

private:
	GLFWwindow* m_windowPointer;
	unsigned int m_width, m_height;
};

inline GLFWwindow* GetWindowPointer()
{
	return Window::GetInstance().GetWindowPointer();
}

