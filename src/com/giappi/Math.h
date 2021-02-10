/* 
 * File:   Math.h
 * Author: Giappi
 *
 * Created on 2021-02-03, 21:46
 */

#include "_typedef.h"

#ifndef MATH_H
#define MATH_H

const char  CHAR_NULL = '\0';

template <class T, const UnsignedInteger N>
struct FixedArray
{
    T data[N];
    inline T   operator [](const UnsignedInteger index) const {return data[index];};
    inline T&  operator [](const UnsignedInteger index)       {return data[index];};
};

struct StringUtils
{
    static void copy(const char* source, UnsignedInteger n, char* dest);
};

template <const UnsignedInteger N>
struct FixedString : public FixedArray<char, N>
{
    FixedString(const char* charArray)
    {
        StringUtils::copy(charArray, N, this->data);
    };
};

#endif /* MATH_H */

