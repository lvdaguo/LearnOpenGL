#pragma once

#include <glad/glad.h>
#include <vector>
#include <iostream>

struct VertexBufferLayoutElement
{
	GLuint type;
	GLuint count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(GLuint type)
	{
		switch (type)
		{
			case GL_FLOAT:
				return sizeof(GLfloat);
			case GL_UNSIGNED_INT:
				return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:
				return sizeof(GLubyte);
		}
		std::cout << "不支持的布局类型" << std::endl;
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() : m_stride(0), m_layoutElements() { }
	~VertexBufferLayout() { };

	const std::vector<VertexBufferLayoutElement>& GetLayoutElements() const { return m_layoutElements; }
	unsigned int GetStride() const { return m_stride; }

	template<typename T>
	void Push(unsigned int count)
	{
	}

	template<>
	void Push<float>(unsigned int count)
	{
		//std::cout << "添加了" << count << "个float类型" << std::endl;
		m_layoutElements.push_back({ GL_FLOAT, count, GL_FALSE});
		m_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_layoutElements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_layoutElements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

private:
	std::vector<VertexBufferLayoutElement> m_layoutElements;
	unsigned int m_stride;
};

