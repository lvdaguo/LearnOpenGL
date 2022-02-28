#include <glad/glad.h> 
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
#include "Texture.h"

const unsigned int width = 800, height = 600;
const std::string window_name = "LearnOpenGL";

std::string vertex_shader_path = "Assets/Shaders/VertexShader.glsl";
std::string fragment_shader_path = "Assets/Shaders/FragmentShader.glsl";

// ͼ�γ�ʼ��
float vertices[] = {
	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};
// �������갴˳ʱ��

// ����
unsigned int indices[] =
{
	0, 1, 3,
	1, 2, 3
};

void ProcessInput(const Renderer& renderer);

int main()
{
	Renderer renderer(width, height, window_name);

	VertexBuffer vbo(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	VertexArray vao;
	vao.AddLayout(vbo, layout);

	IndexBuffer ibo(indices, sizeof(indices) / sizeof(unsigned int));

	Shader shader(vertex_shader_path, fragment_shader_path);

	renderer.SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	Texture texture1("Assets/Textures/container.jpg");
	Texture texture2("Assets/Textures/awesomeface.png");

	shader.Bind();
	shader.SetUniform1i("texture1", 0);
	shader.SetUniform1i("texture2", 1);

	glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::function<void()> draw_statements = [&]()
	{
		ProcessInput(renderer);

		texture1.Bind(0);
		texture2.Bind(1);

		renderer.ClearScreen();
		renderer.Draw(vao, ibo, shader);
	};

	renderer.SetUpdateCallback(draw_statements);
	renderer.Run();

	return 0;
}

void ProcessInput(const Renderer& renderer)
{
	if (renderer.GetKeyDown(Key::Escape))
	{
		std::cout << "�������˳�����ѭ������" << std::endl;
		renderer.Quit();
	}
}