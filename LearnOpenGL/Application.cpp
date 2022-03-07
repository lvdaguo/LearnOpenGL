#include <glad/glad.h> 
// GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD

#include <string>
#include <iostream>
#include <functional>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

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

const std::string vertex_shader_path = "Assets/Shaders/VertexShader.glsl";
const std::string fragment_shader_path = "Assets/Shaders/FragmentShader.glsl";
const std::string light_shader_path = "Assets/Shaders/LightShader.glsl";

const std::string model_path = "Assets/Models/nanosuit/nanosuit.obj";
const std::string model_vertex_shader = "Assets/Shaders/ModelVertexShader.glsl";
const std::string model_fragment_shader = "Assets/Shaders/ModelFragmentShader.glsl";

const std::string& flat_vertex_shader = "Assets/Shaders/FlatVertexShader.glsl";
const std::string& flat_fragment_shader = "Assets/Shaders/FlatFragmentShader.glsl";
const std::string& geometry_shader =      "Assets/Shaders/GeometryShader.glsl";

glm::vec3 camPos = glm::vec3(0.0f, 0.0, 3.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

void InitSingleton();
void ProcessInput();

unsigned int loadCubemap(std::vector<std::string> faces);

// ����Ϊ�����أ���һ��GetInstanceʱ���ù��캯�����չ��죩
// ��ȡ��������˳��Ӧ���ͳ�ʼ��˳��һ��
// �����������˳�ʱ�����������ĵ���˳��Ų�����
Window& window = Window::GetInstance();
Input& input = Input::GetInstance();
Renderer& renderer = Renderer::GetInstance();

int main()
{
	InitSingleton();

	renderer.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	Camera cam(camPos, camUp);

    Model nano(model_path);
    Shader shader(flat_vertex_shader, flat_fragment_shader, geometry_shader);

    renderer.SetUpdateCallback([&]()
	{
		cam.Update();
		ProcessInput();
        renderer.Clear();

        shader.Use();
        shader.SetMatrix4("model", glm::mat4(1.0f));
        shader.SetMatrix4("view", cam.GetViewMatrix());
        shader.SetMatrix4("projection", cam.GetProjectionMatrix());
        shader.SetFloat("time", Helper::GetRealTime());
        renderer.Draw(nano, shader);
	});

	renderer.Run();
	return 0;
}

void InitSingleton()
{
	// ģ��֮��ĳ�ʼ��˳�����Ҫ
	window.Init(width, height, window_name);
	input.Init();
	renderer.Init();
}

void ProcessInput()
{
	if (input.GetKeyDown(Key::Escape))
	{
		std::cout << "�������˳�����ѭ������" << std::endl;
		renderer.Quit();
	}
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}