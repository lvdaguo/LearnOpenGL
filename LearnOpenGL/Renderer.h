#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <functional>
#include "Singleton.h"
#include "Input.h"

/// <summary>
/// ��Ⱦ��
/// </summary>
class Renderer : public Singleton<Renderer>
{
public:
	Renderer();
	~Renderer();
	void Init();

private:
	std::function<void()> m_updateCallback;
	
private:
	// GLAD����λ����opengl�ĺ���ָ��
	void InitGLAD();

public:
	/// <summary>
	/// ����ÿִ֡�еĻص�����
	/// </summary>
	/// <param name="func"> �ص����� </param>
	void SetUpdateCallback(std::function<void()> func) { m_updateCallback = func; }

	void Run();
	void Quit() const { glfwSetWindowShouldClose(Window::GetInstance().GetWindowPointer(), true); }

	void SetClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
	void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	void Draw(const class VertexArray& vertexArray, const class IndexBuffer& indexBuffer, const class Shader& shader);
};

