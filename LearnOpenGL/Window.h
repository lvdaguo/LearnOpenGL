#pragma once

#include <GLFW/glfw3.h>
#include <string>

/// <summary>
/// ´°¿Ú
/// </summary>
class Window
{
public:
	Window(unsigned int width, unsigned int height, const std::string& name);
	~Window();

private:
	void InitGLFW();
	void CreateWindow(unsigned int width, unsigned int height, const std::string& name);
	void SetupCallback();

public:
	GLFWwindow* GetWindow() { return m_window; }

private:
	GLFWwindow* m_window;
};

