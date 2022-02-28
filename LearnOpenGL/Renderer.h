#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <functional>
#include "Input.h"
#include "Window.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

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
	std::function<void()> m_updateCallback;

	// GLAD负责定位所有opengl的函数指针
	void InitGLAD();

public:
	/// <summary>
	/// 设置每帧执行的回调函数
	/// </summary>
	/// <param name="func"> 回调函数 </param>
	void SetUpdateCallback(std::function<void()> func) { m_updateCallback = func; }

	void Run();
	void Quit() const { glfwSetWindowShouldClose(m_window.GetWindowPointer(), true); }

	void SetClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
	void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader);

	bool GetKeyDown(Key key) const
	{
		return glfwGetKey(m_window.GetWindowPointer(), static_cast<int>(key)) == GLFW_PRESS;
	}
};

