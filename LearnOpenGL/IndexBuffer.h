#pragma once

/// <summary>
/// 顶点缓冲
/// </summary>
class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	
	// 禁用了拷贝构造函数，因为移动对象时会调用一次析构函数，将缓冲区和数据错误释放
	// 应当使用uniuqe_ptr，shadered_ptr进行包裹，转移对象所有权或者进行共享
	IndexBuffer(const class IndexBuffer& other) = delete;
	// = 赋值运算符同理
	class IndexBuffer& operator = (const class IndexBuffer& other) = delete;

	~IndexBuffer();

	// 只留下绑定操作，相当于使用此对象，使用完毕后不用解绑
	// 要使用其他对象时，重新绑定其他对象即可
	// 解绑操作不是必须且会造成一定开销，但以防万一，还是将opegl所有解绑操作放在了Helper静态类中
	void Bind() const;

	/// <summary> 获取缓冲个数 </summary>
	unsigned int GetCount() const { return m_count; }

private:
	unsigned int m_bufferID;
	unsigned int m_count;
};

