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
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
	layout.Push<float>(2);

	VertexArray cubeVAO, lightVAO;
	cubeVAO.AddLayout(vbo, layout);
	lightVAO.AddLayout(vbo, layout);

	IndexBuffer ibo(indices, sizeof(indices) / sizeof(unsigned int));

	Shader cubeShader(vertex_shader_path, fragment_shader_path);
	Shader lightShader(vertex_shader_path, light_shader_path);

	renderer.SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	Texture texture3("Assets/Textures/container2.png");
	Texture texture4("Assets/Textures/container2_specular.png");

	glEnable(GL_BLEND);

	glm::vec3 camPos = glm::vec3(0.0f, 0.0, 3.0f);
	Camera cam(camPos, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	renderer.SetUpdateCallback([&]()
	{
		cam.Update();
		ProcessInput();

		renderer.Clear();

		glm::mat4 ViewProjection = cam.GetViewProjectionMatrix();
		cubeShader.Use();

		cubeShader.SetUniform1i("material.diffuse", 0);
		cubeShader.SetUniform1i("material.specular", 1);

		texture3.Bind(0);
		texture4.Bind(1);

		cubeShader.SetUniform1f("material.shininess", 32);

		cubeShader.SetUniformVec3("light.diffuse", glm::vec3(0.8f));
		cubeShader.SetUniformVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		cubeShader.SetUniformVec3("light.ambient", glm::vec3(0.1f));
		// cubeShader.SetUniformVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

		cubeShader.SetUniform1f("light.constant", 1.0f);
		cubeShader.SetUniform1f("light.linear", 0.09f);
		cubeShader.SetUniform1f("light.quadratic", 0.032f);
		cubeShader.SetUniformVec3("light.direction", cam.GetFront());
		cubeShader.SetUniform1f("light.cutOff", glm::cos(glm::radians(12.5f)));
		cubeShader.SetUniform1f("light.outerCutOff", glm::cos(glm::radians(17.5f)));

		cubeShader.SetUniformMat4("ViewProjection", ViewProjection);
		cubeShader.SetUniformVec3("viewPos", cam.GetPosition());
		// cubeShader.SetUniformVec3("lightPos", lightPos);
		cubeShader.SetUniformVec3("lightPos", cam.GetPosition());
		// cubeShader.SetUniformVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		// cubeShader.SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		lightShader.Use();
		lightShader.SetUniformMat4("ViewProjection", ViewProjection);
		lightShader.SetUniformMat4("model", model);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 modell = glm::mat4(1.0f);
			modell = glm::translate(modell, cubePositions[i]);
			float angle = 20.0f * i;
			modell = glm::rotate(modell, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			cubeShader.Use();
			cubeShader.SetUniformMat4("model", modell);

			renderer.Draw(cubeVAO, ibo, cubeShader);
		}
		// renderer.Draw(cubeVAO, ibo, cubeShader);
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