#include <glad/glad.h> 
// GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD

#include "Renderer.h"
#include <iostream>


Renderer::Renderer(unsigned int width, unsigned int height, std::string windowName)
	: m_window(width, height, windowName)
{
	InitGLAD();
}

Renderer::~Renderer()
{
	// 渲染器析构操作
	
	// 窗口成员对象应最后析构
}

void Renderer::InitGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "初始化GLAD失败" << std::endl;
	}
}

void Renderer::Run()
{
	while (glfwWindowShouldClose(m_window.GetWindowPointer()) == false)
	{
		// 每次迭代回调的函数
		m_updateCallback();

		glfwSwapBuffers(m_window.GetWindowPointer());
		glfwPollEvents();
		// glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）
		// glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，
		// 并调用对应的回调函数（可以通过回调方法手动设置）
	}
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader)
{
	vertexArray.Bind();
	indexBuffer.Bind();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, NULL);
}
