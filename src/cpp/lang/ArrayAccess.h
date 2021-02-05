/*
 * File:   ArrayAccess.h
 * Author: Giappi
 *
 * Created on October 14, 2018, 9:53 PM
 */

#ifndef ARRAYACCESS_H
#define ARRAYACCESS_H
#include "_typedef.h"

template <class E>
class ArrayAccess
{
public:

    /**
     * Get element in Array at index
     * @param index index of element in this Array
     * @return the element at the index
     */
    virtual E        operator [](const usize index) const = 0;

    /**
     * Set element in Array at index
     * @param index index of element in this Array
     * @return the element at the index
     */
    virtual E&       operator [](const usize index) = 0;

    /**
     * Check if element exists in Array
     * @param element the element need to check
     * @return true if exists, false otherwise
     */
    virtual boolean  exists(const E& element) = 0;

    /**
     * Get length of this Array
     * @return length of this Array
     */
    virtual usize    getLength() const = 0;


};

#endif /* ARRAYACCESS_H */

