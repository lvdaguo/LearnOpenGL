#include <glad/glad.h>
#include "Input.h"

glm::vec2 Input::m_mousePosition = glm::vec2();
glm::vec2 Input::m_screenCenter = glm::vec2();
Event2<float, float> Input::m_mouseOffsetEvent = Event2<float, float>();
Event2<float, float> Input::m_mouseScrollEvent = Event2<float, float>();

Input::Input() { }

void Input::Init()
{
	const Window& window = Window::GetInstance();

	SetMouseEnabled(false);

	float centerX = window.GetWidth() / static_cast<float>(2);
	float centerY = window.GetHeight() / static_cast<float>(2);
	m_screenCenter = glm::vec2(centerX, centerY);

	glfwSetCursorPosCallback(GetWindowPointer(), MouseCallback);
	glfwSetScrollCallback(GetWindowPointer(), ScrollCallback);
}

Input::~Input() { }

void Input::SetMouseEnabled(bool enabled) const
{
	GLenum mouseStatus = enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
	glfwSetInputMode(GetWindowPointer(), GLFW_CURSOR, mouseStatus);
}

void Input::MouseCallback(GLFWwindow* window, double x, double y)
{
	m_mousePosition = glm::vec2(static_cast<float>(x), static_cast<float>(y));

	// 第一帧时，鼠标上一帧位置设为当前鼠标位置
	static glm::vec2 mousePositionBefore = m_screenCenter;
	
	float xOffset = m_mousePosition.x - mousePositionBefore.x;
	float yOffset = mousePositionBefore.y - m_mousePosition.y;

	m_mouseOffsetEvent.Invoke(xOffset, yOffset);
	mousePositionBefore = m_mousePosition;
}

void Input::ScrollCallback(GLFWwindow* window, double x, double y)
{
	float xOffset = static_cast<float>(x);
	float yOffset = static_cast<float>(y);
	m_mouseOffsetEvent.Invoke(xOffset, yOffset);
}