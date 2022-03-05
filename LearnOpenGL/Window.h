#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include "Singleton.h"

/// <summary>
/// ���ڵ���
/// </summary>
class Window : public Singleton<Window>
{
public:
	Window();
	~Window();
	void Init(unsigned int width, unsigned int height, const std::string& name);

private:
	// GLFW���𴴽����ڣ���������
	void InitGLFW();
	void CreateWindow(unsigned int width, unsigned int height, const std::string& name);
	// ����GLFW�Ļص�
	void SetupCallback();

public:
	GLFWwindow* GetWindowPointer() const { return m_windowPointer; }

	/// <summary> ��ȡ��Ļ��� </summary>
	unsigned int GetWidth() const { return m_width; }
	/// <summary> ��ȡ��Ļ�߶� </summary>
	unsigned int GetHeight() const { return m_height; }
	/// <summary> ��ȡ��Ļ��߱� </summary>
	float GetAspect() const { return static_cast<float>(m_width) / m_height; }

private:
	GLFWwindow* m_windowPointer;
	unsigned int m_width, m_height;
};

inline GLFWwindow* GetWindowPointer()
{
	return Window::GetInstance().GetWindowPointer();
}

