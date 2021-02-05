#pragma once
#include <stddef.h>
#include <vector>
class Memory
{
public:

    #define undefined  ((void*)0xcdcdcdcd)

    template<class T>
    static void Delete(T* &pointer)
    {
        if(pointer != NULL && pointer != undefined)
        {
            delete pointer;
            pointer = NULL;
        }
    }
    template<class T>
    static void Delete(T** &pointer, int n)
    {
        if(pointer != NULL && pointer != undefined)
        {
            for(int i = 0; i < n; i++)
            {
                Delete(pointer[i]);
            }
            delete[] pointer;
            pointer = NULL;
        }
    }
    template<class T>
    static void Delete(std::vector<T*> vector)
    {
        while(vector.size())
        {
            T* t = vector.back();
            Memory::Delete(t);
            t = NULL;
            vector.pop_back();
        }
    }
};
