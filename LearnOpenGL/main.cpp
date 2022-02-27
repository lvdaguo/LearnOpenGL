#include <glad/glad.h> 
#include <GLFW/glfw3.h>

// GLFW���𴴽����ڣ�GLAD����λ����opengl�ĺ���ָ��
// GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD

#include <string>
#include <iostream>
#include <functional>

#include "Renderer.h"
#include "Input.h"

const unsigned int width = 800, height = 600;
const std::string window_name = "LearnOpenGL";

std::string vertex_shader_source =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\n"
;

std::string fragment_shader_source =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n"
;

int main()
{
	Renderer renderer(width, height, window_name);

	// ͼ�γ�ʼ��
	float vertices[] =
	{
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	// �������갴˳ʱ��

	// ����
	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	// VBO VertexBufferObject ���㻺�����
	// VAO VectexArrayObject �����������
	// IBO IndexBufferObject �����������

	// ����VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// ����VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// ����IBO
	unsigned int IBO;
	glGenBuffers(1, &IBO);

	// ��VAO
	glBindVertexArray(VAO);

	// ��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// ��VBO��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ���ĸ�����ָ��������ϣ���Կ���ι�����������ݡ�����������ʽ��
	// GL_STATIC_DRAW  �����ݲ���򼸺�����ı䡣
	// GL_DYNAMIC_DRAW �����ݻᱻ�ı�ܶࡣ
	// GL_STREAM_DRAW  ������ÿ�λ���ʱ����ı䡣

	// ��IBO����������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ���Ӷ�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ���VAO��
	glBindVertexArray(0);

	// ������ɫ��
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	const char* vertex_shader_src = vertex_shader_source.c_str();
	glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
	
	// ������ɫ��
	glCompileShader(vertex_shader);

	// same
	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragment_shader_src = fragment_shader_source.c_str();
	glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);

	glCompileShader(fragment_shader);

	// �������Ƿ����
	int success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	// ������ɫ������
	unsigned int shader_program;
	shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	
	// ���ӳ���
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// ��������Ƿ����
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	// ���û���ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	std::function<void()> draw_statements = [&]()
	{
		if (renderer.GetKeyDown(Key::Escape))
		{
			std::cout << "�������˳�����ѭ������" << std::endl;
			renderer.Quit();
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	};

	renderer.SetUpdateCallback(draw_statements);
	renderer.Run();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteProgram(shader_program);

	return 0;
}