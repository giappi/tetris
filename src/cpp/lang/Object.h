#pragma once

#include "_typedef.h"

// forward declaration
class String;

class Object
{
public:
    Object();
    virtual ~Object();
    /**
     * Compare if two Objects are the same
     * @param object another Object to compare to this
     * @return true if two Object are the same
     */
    virtual boolean     equals(const Object& object) const;
    /**
     * Get name of this Object
     * @return String
     */
    virtual String      getName() const;
    /**
     * Calculate hash code of this Object
     * @return usize
     */
    virtual usize       hashCode() const;
    /**
     * Convert this Object to String
     * @return String
     */
    virtual String      toString() const;
};