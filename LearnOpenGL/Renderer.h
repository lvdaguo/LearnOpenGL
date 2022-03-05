#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include "Singleton.h"
#include "Window.h"

/// <summary>
/// ��Ⱦ������
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
	// GLAD����λ����opengl�ĺ���ָ��
	void InitGLAD();

public:
	/// <summary>
	/// ����ÿִ֡�еĻص�����
	/// </summary>
	/// <param name="func"> �ص����� </param>
	void SetUpdateCallback(std::function<void()> func) { m_updateCallback = func; }

	/// <summary> ��������ʼ��Ⱦѭ�� </summary>
	void Run();
	void Quit() const { glfwSetWindowShouldClose(Window::GetInstance().GetWindowPointer(), true); }

	void SetClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
	void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	void Draw(const class VertexArray& vertexArray, const class IndexBuffer& indexBuffer, const class Shader& shader);
	void Draw(const class Mesh& mesh, class Shader& shader);
	void Draw(const class Model& model, class Shader& shader);
};

