#include <glad/glad.h> 
// GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD

#include <string>
#include <iostream>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "Input.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"
#include "Helper.h"
#include "Event.h"

const unsigned int width = 800, height = 600;
const std::string window_name = "LearnOpenGL";

std::string vertex_shader_path = "Assets/Shaders/VertexShader.glsl";
std::string fragment_shader_path = "Assets/Shaders/FragmentShader.glsl";
std::string light_shader_path = "Assets/Shaders/LightShader.glsl";

// 图形初始化
float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	 -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
// 顶点坐标按顺时针

// 索引
unsigned int indices[] =
{
	0, 1, 2,
	3, 4, 5,
	6, 7, 8,
	9, 10, 11,
	12, 13, 14,
	15, 16, 17,
	18, 19, 20,
	21, 22, 23,
	24, 25, 26,
	27, 28, 29,
	30, 31, 32,
	33, 34, 35
};

void InitSingleton();
void ProcessInput();

Window& window = Window::GetInstance();
Input& input = Input::GetInstance();
Renderer& renderer = Renderer::GetInstance();

int main()
{
	InitSingleton();

	VertexBuffer vbo(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);

	VertexArray cubeVAO, lightVAO;
	cubeVAO.AddLayout(vbo, layout);
	lightVAO.AddLayout(vbo, layout);

	IndexBuffer ibo(indices, sizeof(indices) / sizeof(unsigned int));

	Shader cubeShader(vertex_shader_path, fragment_shader_path);
	Shader lightShader(vertex_shader_path, light_shader_path);

	renderer.SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//Texture texture1("Assets/Textures/container.jpg");
	//Texture texture2("Assets/Textures/awesomeface.png");

	//cubeShader.Use();
	//cubeShader.SetUniform1i("texture1", 0);
	//cubeShader.SetUniform1i("texture2", 1);

	glEnable(GL_BLEND);

	glm::vec3 camPos = glm::vec3(0.0f, 0.0, 3.0f);
	Camera cam(camPos, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	renderer.SetUpdateCallback([&]()
	{
		cam.Update();
		ProcessInput();

		//texture1.Bind(0);
		//texture2.Bind(1);

		renderer.Clear();

		glm::mat4 ViewProjection = cam.GetViewProjectionMatrix();
		cubeShader.Use();

		cubeShader.SetUniformVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
		cubeShader.SetUniformVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		cubeShader.SetUniformVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		cubeShader.SetUniform1f("material.shininess", 32);

		glm::vec3 lightColor;
		lightColor.x = sin(Helper::GetRealTime() * 2.0f);
		lightColor.y = sin(Helper::GetRealTime() * 0.7f);
		lightColor.z = sin(Helper::GetRealTime() * 1.3f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = lightColor * glm::vec3(0.2f);

		cubeShader.SetUniformVec3("light.diffuse", diffuseColor);
		cubeShader.SetUniformVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		cubeShader.SetUniformVec3("light.ambient", ambientColor);

		cubeShader.SetUniformMat4("ViewProjection", ViewProjection);
		cubeShader.SetUniformMat4("model", glm::mat4(1.0f));
		cubeShader.SetUniformVec3("viewPos", camPos);
		cubeShader.SetUniformVec3("lightPos", lightPos);
		cubeShader.SetUniformVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		cubeShader.SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		lightShader.Use();
		lightShader.SetUniformMat4("ViewProjection", ViewProjection);
		lightShader.SetUniformMat4("model", model);

		renderer.Draw(cubeVAO, ibo, cubeShader);
		renderer.Draw(lightVAO, ibo, lightShader);
	});

	renderer.Run();

	return 0;
}

void InitSingleton()
{
	window.Init(width, height, window_name);
	input.Init();
	renderer.Init();
}

void ProcessInput()
{
	if (input.GetKeyDown(Key::Escape))
	{
		std::cout << "按下了退出键，循环结束" << std::endl;
		renderer.Quit();
	}
}