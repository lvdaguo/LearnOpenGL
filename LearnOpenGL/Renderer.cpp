#include <glad/glad.h> 
// GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD

#include <iostream>

#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Helper.h"

Renderer::Renderer(unsigned int width, unsigned int height, std::string windowName) : 
	m_window(width, height, windowName), m_inputModule(m_window),
	m_width(width), m_height(height)
{
	InitGLAD();
	glEnable(GL_DEPTH_TEST);
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
	unsigned int i = 0;
	float m_lastTime = 0.0f;
	while (glfwWindowShouldClose(m_window.GetWindowPointer()) == false)
	{
		float currentTime = static_cast<float>(glfwGetTime());
		float deltaTime = i == 0 ? 0.000000001f : currentTime - m_lastTime;

		while (deltaTime < 0.1f)
		{
			deltaTime += static_cast<float>(glfwGetTime()) - m_lastTime;
		}

		// 设置可以全局获取的时间差
		Helper::SetDeltaTime(deltaTime);

		//std::cout << "第" << i << "帧：时间间隔为" << m_deltaTime * 1000.0
		//	<< "ms，帧数为" << int(1/m_deltaTime) << std::endl;

		// 每次迭代回调的函数
		m_updateCallback(deltaTime);

		glfwSwapBuffers(m_window.GetWindowPointer());
		glfwPollEvents();
		// glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）
		// glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，
		// 并调用对应的回调函数（可以通过回调方法手动设置）

		m_lastTime = currentTime;
		++i;
	}
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader)
{
	vertexArray.Bind();
	indexBuffer.Bind();
	shader.Use();
	glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, NULL);
}
