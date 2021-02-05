#ifndef _TYPEDEFH
#define _TYPEDEFH

#include <stdint.h>
#include <stddef.h>

typedef bool                  boolean;
typedef int8_t                int8;
typedef unsigned char         byte;
typedef int32_t               int32;
typedef int64_t               int64;
typedef size_t                usize;
typedef uint8_t               uint8;
typedef uint32_t              uint32;
typedef uint64_t              uint64;

typedef decltype(nullptr)     Null;
#define null                  nullptr

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