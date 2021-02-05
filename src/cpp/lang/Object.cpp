#include "cpp/lang/Object.h"
#include "cpp/lang/String.h"
#include <typeinfo>

Object::Object()
{
}

Object::~Object()
{
}

boolean Object::equals(const Object& object) const
{
    // @TODO: Implement
    return this == &object;  // !!!WRONG
}

String Object::getName() const
{
    return String(typeid(*this).name());
}

usize Object::hashCode() const
{
    // @TODO: Implement
    return 0; // !!!WRONG
}

String Object::toString() const
{
    return "<Object>";
}

