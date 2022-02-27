#include <glad/glad.h> 
#include <GLFW/glfw3.h>

// GLFW负责创建窗口，GLAD负责定位所有opengl的函数指针
// GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD

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

	// 图形初始化
	float vertices[] =
	{
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	// 顶点坐标按顺时针

	// 索引
	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	// VBO VertexBufferObject 顶点缓冲对象
	// VAO VectexArrayObject 顶点数组对象
	// IBO IndexBufferObject 索引缓冲对象

	// 创建VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// 创建VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// 创建IBO
	unsigned int IBO;
	glGenBuffers(1, &IBO);

	// 绑定VAO
	glBindVertexArray(VAO);

	// 绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 给VBO传输数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
	// GL_STATIC_DRAW  ：数据不会或几乎不会改变。
	// GL_DYNAMIC_DRAW ：数据会被改变很多。
	// GL_STREAM_DRAW  ：数据每次绘制时都会改变。

	// 绑定IBO并传送数据
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 链接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// 解除VAO绑定
	glBindVertexArray(0);

	// 创建着色器
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	const char* vertex_shader_src = vertex_shader_source.c_str();
	glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
	
	// 编译着色器
	glCompileShader(vertex_shader);

	// same
	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragment_shader_src = fragment_shader_source.c_str();
	glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);

	glCompileShader(fragment_shader);

	// 检查编译是否出错
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

	// 创建着色器程序
	unsigned int shader_program;
	shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	
	// 链接程序
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// 检查链接是否出错
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	// 设置绘制模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	std::function<void()> draw_statements = [&]()
	{
		if (renderer.GetKeyDown(Key::Escape))
		{
			std::cout << "按下了退出键，循环结束" << std::endl;
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