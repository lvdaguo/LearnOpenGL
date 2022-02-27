#include <glad/glad.h> 
#include <GLFW/glfw3.h>

// GLFW负责创建窗口，GLAD负责定位所有opengl的函数指针
// GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD

#include <string>
#include <iostream>
#include <functional>

#include "Renderer.h"
#include "Input.h"
#include "Shader.h"

const unsigned int width = 800, height = 600;
const std::string window_name = "LearnOpenGL";

std::string vertex_shader_path = "Assets/Shaders/VertexShader.glsl";
std::string fragment_shader_path = "Assets/Shaders/FragmentShader.glsl";

int main()
{
	Renderer renderer(width, height, window_name);

	// 图形初始化
	float vertices[] =
	{
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};
	// 顶点坐标按顺时针

	// 索引
	unsigned int indices[] =
	{
		0, 1, 3
	};

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// 解除VAO绑定
	glBindVertexArray(0);

	Shader shader(vertex_shader_path, fragment_shader_path);

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

		shader.Bind();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	};

	renderer.SetUpdateCallback(draw_statements);
	renderer.Run();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);

	return 0;
}