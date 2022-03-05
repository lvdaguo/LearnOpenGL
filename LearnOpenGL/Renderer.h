#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include "Singleton.h"
#include "Window.h"

/// <summary>
/// 渲染器单例
/// </summary>
class Renderer : public Singleton<Renderer>
{
public:
	Renderer() = default;
	~Renderer() = default;
	void Init();

private:
	std::function<void()> m_updateCallback;
	
private:
	// GLAD负责定位所有opengl的函数指针
	void InitGLAD();

public:
	/// <summary>
	/// 设置每帧执行的回调函数
	/// </summary>
	/// <param name="func"> 回调函数 </param>
	void SetUpdateCallback(std::function<void()> func) { m_updateCallback = func; }

	/// <summary> 启动，开始渲染循环 </summary>
	void Run();
	void Quit() const { glfwSetWindowShouldClose(Window::GetInstance().GetWindowPointer(), true); }

	void SetClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
	void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	void Draw(const class VertexArray& vertexArray, const class IndexBuffer& indexBuffer, const class Shader& shader);
	void Draw(const class Mesh& mesh, class Shader& shader);
	void Draw(const class Model& model, class Shader& shader);
};

