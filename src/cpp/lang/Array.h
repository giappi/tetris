#pragma once
#include "cpp/lang/Object.h"
#include "cpp/lang/ArrayAccess.h"
#include "Iterable.h"
#include <initializer_list>
#include "utils/Debug.h"

class ArrayBase :
    public Object
{

public:

    typedef byte* E;

    ArrayBase();
    ~ArrayBase();
protected:

    void                    _new();
    E                       _get(const usize index) const;
    E&                      _reference(const usize index);
    void                    _set(const usize index, E element);
    boolean                 _exists(const E& element);
    E                       _getElementAt(const int index);
    usize                   _push(E item);
    E                       _pop();
    usize                   _getLength() const;
    void                    _updateLength();

public:
    const usize &length;

protected:
    void*  _value = null;
    usize  _element_size = 1;
    usize  _length = 0;
};


template <class T>
class Array :
    public ArrayBase,
    public ArrayAccess<T>
{
public:

    Array()
    {
        ArrayBase();
    };

    Array(std::initializer_list<T> list)
    {
        ArrayBase();
        for(auto e : list)
        {
            _push( (byte*) new T(e));
        }
    };


    virtual T               operator [](const usize index) const override
    {
        Debug::logf("-- operator [] get({}) = {}", index, *(T*)_get(index));
        return *(T*)_get(index);
    };

    virtual T&              operator [](const usize index) override
    {
        Debug::logf("-- operator [] set({}) = {}", index, *(T*)_get(index));
        return *(T*)(_reference(index));
    };

    virtual boolean         exists(const T& element) override
    {
        return _exists( (byte*)&element);
    };

    virtual usize           getLength() const override
    {
        return _getLength();
    };

    virtual T               getElementAt(const int index)
    {
        return *(T*)(_getElementAt(index));
    };

    virtual uint32          push(T item)
    {
        return _push((byte*) new T(item));
    };

    T                       pop()
    {
        return *(T*)_pop();
    };

};

