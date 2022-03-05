#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/// <summary>
/// ��̬������
/// </summary>
class Helper
{
private:
	static float m_deltaTime;
	static void SetDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }

	// ��Ⱦ��������Ϊ��Ԫ��ͨ����ÿ֡����deltatime
	friend class Renderer;

	// ȫ��Ψһ��ID�� ����Ψһ���¼��ص�
	static unsigned int m_nextID;

public:
	static unsigned int GenerateID() { return m_nextID++; }

	static float GetRealTime() { return static_cast<float>(glfwGetTime()); }
	static float GetDeltaTime() { return m_deltaTime; }

	// �ָ�opengl��������Ĭ�ϰ�
	static void UnbindVertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	static void UnbindIndexBuffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	static void UnbindVertexArray()
	{
		glBindVertexArray(0);
	}

	static void UnbindShader()
	{
		glUseProgram(0);
	}

	static void UnbindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

