#ifndef SINGLETON_H
#define SINGLETON_H
#include <Qt>

template<class T> T& singleton()
{
    static T* instance {nullptr};
    if (!instance) instance = new T;
    return *instance;
}

template<class T> T& singletonM(T* newInstance = nullptr)
{
    static T* instance {nullptr};
    if (newInstance) instance = newInstance;
    Q_ASSERT(instance);
    return *instance;
}

#endif
