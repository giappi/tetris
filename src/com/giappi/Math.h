/* 
 * File:   Math.h
 * Author: Giappi
 *
 * Created on 2021-02-03, 21:46
 */

#ifndef MATH_H
#define MATH_H

typedef unsigned long long              UnsignedInteger;
typedef long long                       Interger;
typedef bool                            Boolean;

template <class T, const UnsignedInteger N>
struct FixedArray
{
    T data[N];
    inline T   operator [](const UnsignedInteger index) const {return data[index];};
    inline T&  operator [](const UnsignedInteger index)       {return data[index];};
};



#endif /* MATH_H */

