#pragma once

#include <mutex>

template <typename TYPE>
class Singleton
{
public:
	static TYPE& GetInstance()
	{
		std::lock_guard lock(m_lock);
		TYPE* instance = m_instance;
		if (instance == nullptr)
		{
			instance = new TYPE();
			m_instance = instance;
		}
		return *instance;
	}

protected:
	Singleton() {}
	~Singleton() {}

private:
	Singleton(const Singleton&) = delete;
	Singleton operator=(const Singleton&) = delete;

	static TYPE* m_instance;
	static std::mutex m_lock;
};