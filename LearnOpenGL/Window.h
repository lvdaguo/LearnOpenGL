#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include "Input.h"

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
	GLFWwindow* GetWindowPointer() const { return m_windowPointer; }

	unsigned int GetWidth() const { return m_width; }
	unsigned int GetHeight() const { return m_height; }

private:
	GLFWwindow* m_windowPointer;
	unsigned int m_width, m_height;
};

