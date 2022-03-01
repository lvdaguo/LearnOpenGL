#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

/// <summary>
/// æ≤Ã¨π§æﬂ¿‡
/// </summary>
class Helper
{
private:
	static float m_deltaTime;

public:
	static float GetRealTime() { return static_cast<float>(glfwGetTime()); }
	static float GetDeltaTime() { return m_deltaTime; }

	friend void Renderer::Run();

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

