#include <glad/glad.h> 
#include <GLFW/glfw3.h>

// GLFW负责创建窗口，GLAD负责定位所有opengl的函数指针
// GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD

#include <string>
#include <iostream>

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	// 初始化GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建GLFW窗口
	GLFWwindow* window = glfwCreateWindow(width, height, window_name.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "创建GLFW窗口失败" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// 初始化GLAD
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
	{
		std::cout << "初始化GLAD失败" << std::endl;
		return -1;
	}

	// 设置视口
	glViewport(0, 0, width, height);

	// 注册窗口大小更改时的回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 图形初始化
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
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

	// 链接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
		std::cout << "【编译错误】顶点着色器编译失败\n" << infoLog << std::endl;
	}

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << "【编译错误】片段着色器编译失败\n" << infoLog << std::endl;
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
		std::cout << "【链接错误】着色器程序链接失败\n" << infoLog << std::endl;
	}

	while (glfwWindowShouldClose(window) == false)
	{
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader_program);

	// 释放资源
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		std::cout << "按下了退出键，循环结束" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}
}