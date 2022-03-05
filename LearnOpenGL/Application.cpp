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

std::string normal_vertex_shader = "Assets/Shaders/NormalVertexShader.glsl";
std::string normal_fragment_shader = "Assets/Shaders/NormalFragmentShader.glsl";
std::string normal_color_shader = "Assets/Shaders/NormalColorShader.glsl";

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

float cubeVertices[] = {
    // positions          // texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

float planeVertices[] = {
    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
     5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};

unsigned int cube_indices[] = {
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

unsigned int plane_indices[] = {
    0, 1, 2,
    3, 4, 5
};


int main()
{
	InitSingleton();

	renderer.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	Camera cam(camPos, camUp);
	Model model(model_path);

	Shader shader(model_vertex_shader, model_fragment_shader);
	shader.Use();

    VertexBuffer cubeVBO(cubeVertices, sizeof(cubeVertices)), planeVBO(planeVertices, sizeof(planeVertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);

    VertexArray cubeVAO, planeVAO;
    cubeVAO.AddLayout(cubeVBO, layout);
    planeVAO.AddLayout(planeVBO, layout);

    IndexBuffer cubeIBO(cube_indices, 36), planeIBO(plane_indices, 6);

    Texture cubeTexture("Assets/Textures/container.jpg"), planeTexture("Assets/Textures/container2.png");

    Shader normalShader(normal_vertex_shader, normal_fragment_shader);

    Shader outlineShader(normal_vertex_shader, normal_color_shader);
    outlineShader.Use();
    outlineShader.SetVector3("color", glm::vec3(0.3f, 0.4f, 0.5f));

    //glDepthFunc(GL_ALWAYS);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
    renderer.SetUpdateCallback([&]()
	{
		cam.Update();
		ProcessInput();
        // renderer.Clear();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glStencilMask(0x00);

        // draw floor
        planeTexture.Bind();
        normalShader.SetMatrix4("model", glm::mat4(1.0f));
        renderer.Draw(planeVAO, planeIBO, normalShader);

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        // draw two containers
        cubeTexture.Bind();

        normalShader.Use();
		glm::mat4 view_projection = cam.GetViewProjectionMatrix();
        normalShader.SetMatrix4("view_projection", view_projection);

		glm::mat4 mod = glm::mat4(1.0f);
		mod = glm::translate(mod, glm::vec3(-1.0f, 0.0f, -1.0f));
        normalShader.SetMatrix4("model", mod);
        renderer.Draw(cubeVAO, cubeIBO, normalShader);

        mod = glm::mat4(1.0f);
        mod = glm::translate(mod, glm::vec3(2.0f, 0.0f, 0.0f));
        normalShader.SetMatrix4("model", mod);
        renderer.Draw(cubeVAO, cubeIBO, normalShader);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        outlineShader.Use();
        outlineShader.SetMatrix4("view_projection", view_projection);

        mod = glm::mat4(1.0f);
        mod = glm::translate(mod, glm::vec3(-1.0f, 0.0f, -1.0f));
        mod = glm::scale(mod, glm::vec3(1.1f));
        outlineShader.SetMatrix4("model", mod);
        renderer.Draw(cubeVAO, cubeIBO, outlineShader);

        mod = glm::mat4(1.0f);
        mod = glm::translate(mod, glm::vec3(2.0f, 0.0f, 0.0f));
        mod = glm::scale(mod, glm::vec3(1.1f));
        outlineShader.SetMatrix4("model", mod);
        renderer.Draw(cubeVAO, cubeIBO, outlineShader);

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glEnable(GL_DEPTH_TEST);

        //shader.SetMatrix4("view_projection", view_projection);
		//shader.SetMatrix4("model", mod);
		//renderer.Draw(vao, ibo, shader);
		//renderer.Draw(model, shader);
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