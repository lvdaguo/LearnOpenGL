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
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

const unsigned int width = 800, height = 600;
const std::string window_name = "LearnOpenGL";

std::string vertex_shader_path = "Assets/Shaders/VertexShader.glsl";
std::string fragment_shader_path = "Assets/Shaders/FragmentShader.glsl";

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
			std::cout << "按下了退出键，循环结束" << std::endl;
			renderer.Quit();
		}

		renderer.ClearScreen();
		renderer.Draw(vao, ibo, shader);
	};

	renderer.SetUpdateCallback(draw_statements);
	renderer.Run();

	return 0;
}