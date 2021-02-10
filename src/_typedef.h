#ifndef _TYPEDEFH
#define _TYPEDEFH

//#include <stdint.h>
//#include <stddef.h>

/** Machine Basic Type */
typedef bool                    boolean;
typedef unsigned char           byte;
typedef signed char             int8;
typedef unsigned char           uint8;
typedef signed int              int32;
typedef unsigned int            uint32;

__extension__ typedef signed   long long int    int64;
__extension__ typedef unsigned long long int    uint64;

/** type which has size of RAM */
#ifdef __SIZE_TYPE__
    typedef __SIZE_TYPE__ usize;
#else
    typedef long unsigned int usize;
#endif //__SIZE_TYPE__

typedef bool                    Boolean;
typedef uint64                  NonNegInteger;
typedef NonNegInteger           UnsignedInteger;
typedef int64                   Integer;

typedef decltype(nullptr)       Null;
#define null                    nullptr

#if 0
#include "utils/SharedPointer.h"
#define MAKE_TYPE(CLASS_NAME) SharedPointer<class##CLASS_NAME>
#define DEFINE_POINTER(CLASS_NAME) typedef MAKE_TYPE(CLASS_NAME) CLASS_NAME
#define NEW(CLASS_NAME, __VA_ARGS) MAKE_TYPE(CLASS_NAME)(new class##CLASS_NAME(__VA_ARGS))
#endif

//class Object;
//class String;

//DEFINE_POINTER(Object);
//DEFINE_POINTER(String);

#endif /* _TYPEDEFH */