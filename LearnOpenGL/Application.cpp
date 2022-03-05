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
#include "Camera.h"
#include "Model.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

const unsigned int width = 1280, height = 720;
const std::string window_name = "LearnOpenGL";

std::string vertex_shader_path = "Assets/Shaders/VertexShader.glsl";
std::string fragment_shader_path = "Assets/Shaders/FragmentShader.glsl";
std::string light_shader_path = "Assets/Shaders/LightShader.glsl";

std::string model_path = "Assets/Models/nanosuit/nanosuit.obj";
std::string model_vertex_shader = "Assets/Shaders/ModelVertexShader.glsl";
std::string model_fragment_shader = "Assets/Shaders/ModelFragmentShader.glsl";

glm::vec3 camPos = glm::vec3(0.0f, 0.0, 3.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

void InitSingleton();
void ProcessInput();

// 单例为懒加载，第一次GetInstance时调用构造函数（空构造）
// 获取单例引用顺序应当和初始化顺序一致
// 这样当程序退出时，析构函数的调用顺序才不出错
Window& window = Window::GetInstance();
Input& input = Input::GetInstance();
Renderer& renderer = Renderer::GetInstance();

int main()
{
	InitSingleton();

	renderer.SetClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	Camera cam(camPos, camUp);
	Model model(model_path);

	Shader shader(model_vertex_shader, model_fragment_shader);
	shader.Use();

	renderer.SetUpdateCallback([&]()
	{
		cam.Update();
		ProcessInput();

		renderer.Clear();

		glm::mat4 view_projection = cam.GetViewProjectionMatrix();
		shader.SetMatrix4("view_projection", view_projection);
		glm::mat4 mod = glm::mat4(1.0f);
		mod = glm::translate(mod, glm::vec3(0.0f, 0.0f, 0.0f));
		mod = glm::scale(mod, glm::vec3(1.0f));
		shader.SetMatrix4("model", mod);
		//renderer.Draw(vao, ibo, shader);
		renderer.Draw(model, shader);
	});

	renderer.Run();

	return 0;
}

void InitSingleton()
{
	// 模块之间的初始化顺序很重要
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