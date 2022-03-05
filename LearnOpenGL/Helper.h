#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/// <summary>
/// 静态工具类
/// </summary>
class Helper
{
private:
	static float m_deltaTime;
	static void SetDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }

	// 渲染器单例作为友元，通过其每帧更新deltatime
	friend class Renderer;

	// 全局唯一的ID， 用于唯一化事件回调
	static unsigned int m_nextID;

public:
	static unsigned int GenerateID() { return m_nextID++; }

	static float GetRealTime() { return static_cast<float>(glfwGetTime()); }
	static float GetDeltaTime() { return m_deltaTime; }

	// 恢复opengl各类对象的默认绑定
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

