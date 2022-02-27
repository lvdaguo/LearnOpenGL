#pragma once

#include "Window.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

/// <summary>
/// ��Ⱦ��
/// </summary>
class Renderer
{
public:
	Renderer(unsigned int width, unsigned int height, std::string windowName);
	~Renderer();

private:
	Window m_window;
	std::function<void()> m_updateCallback;

	// GLAD����λ����opengl�ĺ���ָ��
	void InitGLAD();

public:
	void SetUpdateCallback(std::function<void()> func) { m_updateCallback = func; }
	void Run();
	void Quit() { glfwSetWindowShouldClose(m_window.GetWindowPointer(), true); }

	bool GetKeyDown(Key key)
	{
		return glfwGetKey(m_window.GetWindowPointer(), static_cast<int>(key)) == GLFW_PRESS;
	}
};

