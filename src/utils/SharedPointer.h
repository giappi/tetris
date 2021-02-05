/*
 * File:   SharedPointer.h
 * Author: Giappi
 *
 * Created on April 26, 2018, 10:21 PM
 */

#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H
#include <memory>

template <class T>
class SharedPointer: public std::shared_ptr<T>
{
    using std::shared_ptr<T>::shared_ptr;
public:
    SharedPointer(){};
    SharedPointer(T* that): std::shared_ptr<T>::shared_ptr(that){};
    // for String type
    SharedPointer(const char* str): std::shared_ptr<T>::shared_ptr(new T(str)){};
    SharedPointer<T> operator+(const SharedPointer<T>& that)
    {
        return this->get()->operator+(that);
    };

};


#endif /* SHAREDPOINTER_H */

