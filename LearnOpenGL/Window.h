#pragma once

#include <GLFW/glfw3.h>
#include <string>

/// <summary>
/// ����
/// </summary>
class Window
{
public:
	Window(unsigned int width, unsigned int height, const std::string& name);
	~Window();

private:
	// GLFW���𴴽����ڣ���������
	void InitGLFW();
	void CreateWindow(unsigned int width, unsigned int height, const std::string& name);
	void SetupCallback();

public:
	GLFWwindow* GetWindowPointer() const { return m_window; }

private:
	GLFWwindow* m_window;
};
