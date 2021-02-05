/*
 * File:   PointerCOA.h
 * Author: Giappi
 *
 * Created on October 31, 2018, 8:55 PM
 */

#ifndef POINTERCOA_H
#define POINTERCOA_H
#include "_typedef.h"
#include "Memory.h"



/**
 * Copy On Assign Pointer
 * -- Condition: value of type T is copyable
 * -- ( have copy constructor and assignment operator )
 * -- Class is not abstract
 */
template <class T>
class PointerCOA
{
public:

    PointerCOA& operator=(const PointerCOA& another)
    {
        if(&another != this)
        {
            return this->operator=(another._value);
        }
        return *this;
    };

    PointerCOA& operator=(T* __raw_pointer)
    {
        if(this->_value != __raw_pointer)
        {
            if(__raw_pointer != null)
            {
                T t_value = *__raw_pointer;
                if(_value == null)
                {
                    _value = Memory::allocate<T>(t_value);
                }
                else
                {
                    *_value = t_value;
                }
            }
            else
            {
                if(_value != null)
                {
                    Memory::unallocate(_value);
                    _value = null;
                }
                else
                {
                    _value = __raw_pointer;
                }
            }
        }
        return *this;
    };

    T* operator->()
    {
        return _value;
    }

    T& operator*()
    {
        return *_value;
    };

    PointerCOA(const PointerCOA<T>& another)
    {
        if(another._value != null)
        {
            _value = Memory::allocate<T>(*(another._value));
        }
        else
        {
            _value = null;
        }
    };

    PointerCOA(T* __raw_pointer)
    {
        if(__raw_pointer != null)
        {
            _value = Memory::allocate<T>(*(__raw_pointer));
        }
        else
        {
            _value = null;
        }
    };

    PointerCOA(Null null_pointer)
    {
        _value = null;
    };

    template <class... Args>
    PointerCOA(Args... args)
    {
        _value = Memory::allocate<T>(args...);
    };

    virtual ~PointerCOA()
    {
        Memory::unallocate(_value);
    };

private:
    T* _value;
};

#endif /* POINTERCOA_H */

