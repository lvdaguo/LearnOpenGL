#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Singleton.h"
#include "Window.h"
#include "Event.h"

/// <summary>
/// ����ö��
/// </summary>
enum class Key
{
	Escape = GLFW_KEY_ESCAPE,
	W = GLFW_KEY_W,
	A = GLFW_KEY_A,
	S = GLFW_KEY_S,
	D = GLFW_KEY_D
};

/// <summary>
/// ���뵥��
/// </summary>
class Input : public Singleton<Input>
{
public:
	Input() = default;
	~Input() = default;
	void Init();

	/// <summary> ��ʾ��꣬������� </summary>
	void SetMouseEnabled(bool enabled) const;

	/// <summary> ��ⰴ������ </summary>
	bool GetKeyDown(enum class Key key) const
	{
		return glfwGetKey(GetWindowPointer(), static_cast<int>(key)) == GLFW_PRESS;
	}

	/// <summary> ��ȡ��굱ǰ����Ļ���꣨����λ�ã� </summary>
	glm::vec2 GetMousePosition() const { return m_mousePosition; }

	/// <summary> ��ȡ���λ��ƫ���¼� </summary>
	static class Event2<float, float>& GetMouseOffsetEvent() { return m_mouseOffsetEvent; }
	
	/// <summary> ��ȡ������ƫ���¼� </summary>
	static class Event2<float, float>& GetMouseScrollEvent() { return m_mouseScrollEvent; }

private:
	// ʹ��Window�����е�GLFWwindowָ��
	// ����GLFW�е�����¼��ص��������Ƿǳ�Ա������
	static void MouseCallback(GLFWwindow* window, double x, double y);
	static void ScrollCallback(GLFWwindow* window, double x, double y);

	static class Event2<float, float> m_mouseOffsetEvent;
	static class Event2<float, float> m_mouseScrollEvent;

	static glm::vec2 m_screenCenter;
	static glm::vec2 m_mousePosition;
};

