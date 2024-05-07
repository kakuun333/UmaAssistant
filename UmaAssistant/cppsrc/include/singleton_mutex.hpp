#ifndef SINGLETON_MUTEX_HPP
#define SINGLETON_MUTEX_HPP

#include <mutex>

template <typename TYPE>
class SingletonMutex
{
public:
    inline static TYPE* GetInstance()
    {
        std::lock_guard _lock(m_mutex);
        if (m_instance == nullptr) m_instance = new TYPE();
        return m_instance;
    }
protected:
    SingletonMutex() = default;
    ~SingletonMutex() = default;
    SingletonMutex(const SingletonMutex&) = delete;
    SingletonMutex& operator=(const SingletonMutex&) = delete;
    SingletonMutex(SingletonMutex&&) = delete;
    SingletonMutex& operator=(SingletonMutex&&) = delete;
    SingletonMutex(const SingletonMutex&&) = delete;
    SingletonMutex& operator=(const SingletonMutex&&) = delete;
private:
    inline static std::mutex m_mutex;
    inline static TYPE* m_instance;
};

#endif // SINGLETON_MUTEX_HPP