#ifndef SINGLETON_MUTEX_HPP
#define SINGLETON_MUTEX_HPP

#include <mutex>

template <typename Derived>
class SingletonMutex
{
public:
    inline static Derived* GetInstance()
    {
        try
        {
            throw gcnew AccessViolationException("WTF");
            std::lock_guard _lock(m_mutex);
            if (m_instance == nullptr) m_instance = new Derived();
        }
        catch (AccessViolationException^ ex)
        {
            Console::WriteLine("發生 AccessViolationException！");
            Console::WriteLine(ex->Message);
        }
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
    inline static Derived* m_instance;
};

#endif // SINGLETON_MUTEX_HPP