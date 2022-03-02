#pragma once

#include <unordered_map>
#include <functional>
#include "Action.h"

class Event
{
public:
	typedef std::function<void()> func_t;
	typedef Action action_t;

	Event() { }
	~Event() { }

	void Invoke()
	{
		for (auto& pair : m_actions)
		{
			func_t& func = pair.second;
			func();
		}
	}

	void Add(const action_t& action)
	{
		m_actions.emplace(action.GetID(), action.GetFunction());
	}

	void Remove(const action_t& action)
	{
		auto it = m_actions.find(action.GetID());
		if (it == m_actions.end()) return;
		m_actions.erase(it);
	}

	void Clear()
	{
		m_actions.clear();
	}

	Event& operator +=(const action_t& action)
	{
		Add(action);
		return *this;
	}

	Event& operator -=(const action_t& action)
	{
		Remove(action);
		return *this;
	}

private:
	std::unordered_map<unsigned int, func_t> m_actions;
};

template<typename T>
class Event1
{
public:
	typedef std::function<void(T)> func_t;
	typedef Action1<T> action_t;

	Event1() { }
	~Event1() { }

	void Invoke(T t)
	{
		for (auto& pair : m_actions) 
		{
			func_t& func = pair.second;
			func(t);
		}
	}

	void Add(const action_t& action)
	{
		m_actions.emplace(action.GetID(), action.GetFunction());
	}

	void Remove(const action_t& action)
	{
		auto it = m_actions.find(action.GetID());
		if (it == m_actions.end()) return;
		m_actions.erase(it);
	}

	void Clear()
	{
		m_actions.clear();
	}

	Event1<T>& operator +=(const action_t& action)
	{
		Add(action);
		return *this;
	}
	
	Event1<T>& operator -=(const action_t& action)
	{
		Remove(action);
		return *this;
	}

private:
	std::unordered_map<unsigned int, func_t> m_actions;
};

template<typename T, typename U>
class Event2
{
public:
	typedef std::function<void(T, U)> func_t;
	typedef Action2<T, U> action_t;

	Event2() { }
	~Event2() { }

	void Invoke(T t, U u)
	{
		for (auto& pair : m_actions)
		{
			func_t& func = pair.second;
			func(t, u);
		}
	}

	void Add(const action_t& action)
	{
		m_actions.emplace(action.GetID(), action.GetFunction());
	}

	void Remove(const action_t& action)
	{
		auto it = m_actions.find(action.GetID());
		if (it == m_actions.end()) return;
		m_actions.erase(it);
	}

	void Clear()
	{
		m_actions.clear();
	}

	Event2<T, U>& operator +=(const action_t& action)
	{
		Add(action);
		return *this;
	}

	Event2<T, U>& operator -=(const action_t& action)
	{
		Remove(action);
		return *this;
	}

private:
	std::unordered_map<unsigned int, func_t> m_actions;
};

template<typename T, typename U, typename V>
class Event3
{
public:
	typedef std::function<void(T, U, V)> func_t;
	typedef Action3<T, U, V> action_t;

	Event3() { }
	~Event3() { }

	void Invoke(T t, U u, V v)
	{
		for (auto& pair : m_actions)
		{
			func_t& func = pair.second;
			func(t, u, v);
		}
	}

	void Add(const action_t& action)
	{
		m_actions.emplace(action.GetID(), action.GetFunction());
	}

	void Remove(const action_t& action)
	{
		auto it = m_actions.find(action.GetID());
		if (it == m_actions.end()) return;
		m_actions.erase(it);
	}

	void Clear()
	{
		m_actions.clear();
	}

	Event3<T, U, V>& operator +=(const action_t& action)
	{
		Add(action);
		return *this;
	}

	Event3<T, U, V>& operator -=(const action_t& action)
	{
		Remove(action);
		return *this;
	}

private:
	std::unordered_map<unsigned int, func_t> m_actions;
};

template<typename T, typename U, typename V, typename W>
class Event4
{
public:
	typedef std::function<void(T, U, V, W)> func_t;
	typedef Action4<T, U, V, W> action_t;

	Event4() { }
	~Event4() { }

	void Invoke(T t, U u, V v, W w)
	{
		for (auto& pair : m_actions)
		{
			func_t& func = pair.second;
			func(t, u, v, w);
		}
	}

	void Add(const action_t& action)
	{
		m_actions.emplace(action.GetID(), action.GetFunction());
	}

	void Remove(const action_t& action)
	{
		auto it = m_actions.find(action.GetID());
		if (it == m_actions.end()) return;
		m_actions.erase(it);
	}

	void Clear()
	{
		m_actions.clear();
	}

	Event4<T, U, V, W>& operator +=(const action_t& action)
	{
		Add(action);
		return *this;
	}

	Event4<T, U, V, W>& operator -=(const action_t& action)
	{
		Remove(action);
		return *this;
	}

private:
	std::unordered_map<unsigned int, func_t> m_actions;
};