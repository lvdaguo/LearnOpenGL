#include "Input.h"
#include "Window.h"

glm::vec2 InputModule::m_mousePosition = glm::vec2();
glm::vec2 InputModule::m_screenCenter = glm::vec2();
std::vector<std::function<void(float, float)>> InputModule::m_mouseOffsetCallback = { };
std::vector<std::function<void(float, float)>> InputModule::m_mouseScrollCallback = { };

InputModule::InputModule(const Window& window) : 
	m_windowPointer(window.GetWindowPointer())
{
	SetMouseEnabled(false);

	float centerX = window.GetWidth() / static_cast<float>(2);
	float centerY = window.GetHeight() / static_cast<float>(2);
	m_screenCenter = glm::vec2(centerX, centerY);

	glfwSetCursorPosCallback(m_windowPointer, MouseCallback);
	glfwSetScrollCallback(m_windowPointer, ScrollCallback);
}

InputModule::~InputModule() { }

void InputModule::SetMouseEnabled(bool enabled) const
{
	GLenum mouseStatus = enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
	glfwSetInputMode(m_windowPointer, GLFW_CURSOR, mouseStatus);
}

void InputModule::MouseCallback(GLFWwindow* window, double x, double y)
{
	m_mousePosition = glm::vec2(static_cast<float>(x), static_cast<float>(y));

	// 第一帧时，鼠标上一帧位置设为当前鼠标位置
	static glm::vec2 mousePositionBefore = m_screenCenter;
	
	float xOffset = m_mousePosition.x - mousePositionBefore.x;
	float yOffset = mousePositionBefore.y - m_mousePosition.y;

	for (auto callback : m_mouseOffsetCallback) callback(xOffset, yOffset);
	mousePositionBefore = m_mousePosition;
}

void InputModule::ScrollCallback(GLFWwindow* window, double x, double y)
{
	float xOffset = static_cast<float>(x);
	float yOffset = static_cast<float>(y);
	for (auto callback : m_mouseScrollCallback) callback(xOffset, yOffset);
}