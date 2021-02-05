#include "cpp/lang/Array.h"
#include <exception>
#include <stdexcept>
#include <vector>
#include <algorithm>

typedef std::vector<ArrayBase::E> StdVector;

#pragma region HELP_FUNCTIONS

inline StdVector&               VECTOR(void* __void_pointer)
{
    return *((StdVector*)__void_pointer);
}

#pragma endregion HELP_FUNCTIONS

void ArrayBase::_new()
{
    this->_value = new StdVector(0);
    _updateLength();
}

ArrayBase::ArrayBase() : length(_length)
{
    _new();
    _length = 0;
}

boolean ArrayBase::_exists(const E& __element)
{
    auto v = VECTOR(_value);
    return std::find(v.begin(), v.end(), __element) != v.end();
}

ArrayBase::E ArrayBase::_get(const usize __index) const
{
    return VECTOR(_value)[__index];
}

ArrayBase::E ArrayBase::_getElementAt(const int __index)
{
    return _get(__index);
}

ArrayBase::E ArrayBase::_pop()
{
    auto e = VECTOR(_value).back();
    VECTOR(_value).pop_back();
    _updateLength();
    return e;
}

usize ArrayBase::_push(E item)
{

    VECTOR(_value).push_back(item);
    _updateLength();
    return _length;
}

ArrayBase::E& ArrayBase::_reference(const usize __index)
{
    return (VECTOR(_value)[__index]);
}

void ArrayBase::_set(const usize index, E element)
{

}

usize ArrayBase::_getLength() const
{
    return VECTOR(_value).size();
}


void ArrayBase::_updateLength()
{
    _length = _getLength();
}

ArrayBase::~ArrayBase()
{
    delete (StdVector*) _value;
}
