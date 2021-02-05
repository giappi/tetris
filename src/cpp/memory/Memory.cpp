/*
 * File:   Memory.cpp
 * Author: Giappi
 *
 * Created on October 29, 2018, 9:56 PM
 */

#include "Memory.h"
#include "utils/Debug.h"

bool Memory::debug = false;

void Memory::__debug__log(Action __action, uint64 __size, const char*  __typeName, const char* __note)
{
    if(Memory::debug)
    {
        // @important Don't use Debug.logf(...). Because it it use String type, that also use Memory -> recursive
        Debug::log("%s {%s} with %u bytes. %s", (__action == Action::NEW ? "Allocate" : "Delete"), __typeName, __size, __note);
    }
}
