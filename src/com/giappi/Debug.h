
#pragma once

#include <typeinfo>
#include <assert.h>
#include <chrono>

int __printf__(const char* strformat, ...);

class performance
{
public:
	static std::chrono::system_clock::time_point t;

public:
	static double now();
	static void begin();
	static double end();

};
