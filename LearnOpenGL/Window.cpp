#include "Window.h"
#include <iostream>
#include <functional>

Window::Window(unsigned int width, unsigned int height, const std::string& name)
{
	InitGLFW();
	CreateWindow(width, height, name);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::InitGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::CreateWindow(unsigned int width, unsigned int height, const std::string& name)
{
	m_windowPointer = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (m_windowPointer == NULL)
	{
		std::cout << "´´½¨GLFW´°¿ÚÊ§°Ü" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_windowPointer);

	SetupCallback();

}

void Window::SetupCallback()
{
	glfwSetFramebufferSizeCallback(m_windowPointer, [](GLFWwindow*, int width, int height)
	{
		glViewport(0, 0, width, height);
	});
}
