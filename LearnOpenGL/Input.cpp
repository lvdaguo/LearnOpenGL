#include "Input.h"

glm::vec2 Input::m_mousePosition = glm::vec2();
glm::vec2 Input::m_screenCenter = glm::vec2();
std::vector<std::function<void(float, float)>> Input::m_mouseOffsetCallback = { };
std::vector<std::function<void(float, float)>> Input::m_mouseScrollCallback = { };

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

	// ��һ֡ʱ�������һ֡λ����Ϊ��ǰ���λ��
	static glm::vec2 mousePositionBefore = m_screenCenter;
	
	float xOffset = m_mousePosition.x - mousePositionBefore.x;
	float yOffset = mousePositionBefore.y - m_mousePosition.y;

	for (auto callback : m_mouseOffsetCallback) callback(xOffset, yOffset);
	mousePositionBefore = m_mousePosition;
}

void Input::ScrollCallback(GLFWwindow* window, double x, double y)
{
	float xOffset = static_cast<float>(x);
	float yOffset = static_cast<float>(y);
	for (auto callback : m_mouseScrollCallback) callback(xOffset, yOffset);
}