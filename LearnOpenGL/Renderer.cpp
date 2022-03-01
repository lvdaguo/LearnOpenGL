#include <glad/glad.h> 
// GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD

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
	// ��Ⱦ����������
	
	// ���ڳ�Ա����Ӧ�������
}

void Renderer::InitGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "��ʼ��GLADʧ��" << std::endl;
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

		// ���ÿ���ȫ�ֻ�ȡ��ʱ���
		Helper::SetDeltaTime(deltaTime);

		//std::cout << "��" << i << "֡��ʱ����Ϊ" << m_deltaTime * 1000.0
		//	<< "ms��֡��Ϊ" << int(1/m_deltaTime) << std::endl;

		// ÿ�ε����ص��ĺ���
		m_updateCallback(deltaTime);

		glfwSwapBuffers(m_window.GetWindowPointer());
		glfwPollEvents();
		// glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩
		// glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬��
		// �����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�

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
