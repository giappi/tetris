/*
 * File:   Iterable.h
 * Author: Giappi
 *
 * Created on October 14, 2018, 11:13 PM
 */

#ifndef ITERABLE_H
#define ITERABLE_H

template <class T>
class Iterable
{
public:

    virtual T* begin() = 0;
    virtual T* end() = 0;

};

#endif /* ITERABLE_H */

