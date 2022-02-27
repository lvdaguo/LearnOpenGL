#pragma once

#include <GLFW/glfw3.h>
#include <string>

/// <summary>
/// 窗口
/// </summary>
class Window
{
public:
	Window(unsigned int width, unsigned int height, const std::string& name);
	~Window();

private:
	// GLFW负责创建窗口，管理输入
	void InitGLFW();
	void CreateWindow(unsigned int width, unsigned int height, const std::string& name);
	void SetupCallback();

public:
	GLFWwindow* GetWindowPointer() { return m_window; }

private:
	GLFWwindow* m_window;
};

