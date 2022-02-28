#include <glad/glad.h> 
#include <GLFW/glfw3.h>

// GLFW���𴴽����ڣ�GLAD����λ����opengl�ĺ���ָ��
// GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD

#include <string>
#include <iostream>
#include <functional>

#include "Renderer.h"
#include "Input.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

const unsigned int width = 800, height = 600;
const std::string window_name = "LearnOpenGL";

std::string vertex_shader_path = "Assets/Shaders/VertexShader.glsl";
std::string fragment_shader_path = "Assets/Shaders/FragmentShader.glsl";

// ͼ�γ�ʼ��
float vertices[] =
{
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
};
// �������갴˳ʱ��

// ����
unsigned int indices[] =
{
	0, 1, 2
};

int main()
{
	Renderer renderer(width, height, window_name);

	VertexBuffer vbo(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);

	VertexArray vao;
	vao.AddLayout(vbo, layout);

	IndexBuffer ibo(indices, sizeof(indices) / sizeof(unsigned int));

	Shader shader(vertex_shader_path, fragment_shader_path);

	renderer.SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	std::function<void()> draw_statements = [&]()
	{
		if (renderer.GetKeyDown(Key::Escape))
		{
			std::cout << "�������˳�����ѭ������" << std::endl;
			renderer.Quit();
		}

		renderer.ClearScreen();
		renderer.Draw(vao, ibo, shader);
	};

	renderer.SetUpdateCallback(draw_statements);
	renderer.Run();

	return 0;
}