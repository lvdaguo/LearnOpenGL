#include <glad/glad.h> 
// GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD

#include "Renderer.h"
#include <iostream>


Renderer::Renderer(unsigned int width, unsigned int height, std::string windowName)
	: m_window(width, height, windowName)
{
	InitGLAD();
}

Renderer::~Renderer()
{
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
	while (glfwWindowShouldClose(m_window.GetWindow()) == false)
	{
		// ÿ�ε����ص��ĺ���
		m_updateCallback();

		glfwSwapBuffers(m_window.GetWindow());
		glfwPollEvents();
		// glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��
		// ������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
		// glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬��
		// �����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
	}
}
