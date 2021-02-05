/*
 * File:   Memory.h
 * Author: Giappi
 *
 * Created on October 29, 2018, 9:56 PM
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <typeinfo>

class Memory
{

public:

    template <class T, class... Args>
    static T* allocate(Args... args)
    {
        __debug__log(Action::NEW, sizeof(T), typeid(T).name());
        return new T(args...);
    };

    template <class T>
    static void unallocate(T* &pointer)
    {
        __debug__log(Action::DELETE, sizeof(T), typeid(T).name());
        delete pointer;
        pointer = nullptr;
    }

    template <class T>
    static void unallocate(T*&& pointer)
    {
        __debug__log(Action::DELETE, sizeof(T), typeid(T).name(), "[r-value]");
        delete pointer;
        pointer = nullptr;
    }

private:

    enum class Action { NEW, DELETE};
    typedef unsigned long long int uint64;
    static void __debug__log(Action action, uint64 size, const char* typeName, const char* note = "");

public:
    static bool debug;
};

#endif /* MEMORY_H */

