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
	while (glfwWindowShouldClose(m_window.GetWindowPointer()) == false)
	{
		// ÿ�ε����ص��ĺ���
		m_updateCallback();

		glfwSwapBuffers(m_window.GetWindowPointer());
		glfwPollEvents();
		// glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩
		// glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬��
		// �����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
	}
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader)
{
	vertexArray.Bind();
	indexBuffer.Bind();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, NULL);
}
