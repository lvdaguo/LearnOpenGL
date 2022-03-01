#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <functional>
#include "Window.h"
#include "Input.h"

/// <summary>
/// 渲染器
/// </summary>
class Renderer
{
public:
	Renderer(unsigned int width, unsigned int height, std::string windowName);
	~Renderer();

private:
	Window m_window;
	InputModule m_inputModule;
	unsigned int m_width, m_height;

	std::function<void(float)> m_updateCallback;

public:
	unsigned int GetWidth() const { return m_width; }
	unsigned int GetHeight() const { return m_height; }
	float GetAspect() const { return static_cast<float>(m_width) / m_height; }
	
	const InputModule& GetInputModule() const { return m_inputModule; }

private:
	// GLAD负责定位所有opengl的函数指针
	void InitGLAD();

public:
	/// <summary>
	/// 设置每帧执行的回调函数
	/// </summary>
	/// <param name="func"> 回调函数 </param>
	void SetUpdateCallback(std::function<void(float)> func) { m_updateCallback = func; }

	void Run();
	void Quit() const { glfwSetWindowShouldClose(m_window.GetWindowPointer(), true); }

	void SetClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
	void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	void Draw(const class VertexArray& vertexArray, const class IndexBuffer& indexBuffer, const class Shader& shader);
};

