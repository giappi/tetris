#include "Debug.h"
#include <string>
#include <stdarg.h>

#ifdef _WIN32
#include <Windows.h>
#include <time.h>
// disable warning deprecate on windows OS
#pragma warning(disable : 4996)

//Get console to handle
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

#endif

int COLOR_DEFAULT = 0x08;
int COLOR_TIME    = 0x0B;
int COLOR_NUMBER  = 0x06;
int COLOR_STRING  = 0x06;



void __print_value__(const char* text, int color)
{
#ifdef _WIN32
	// Set color to cyan
	SetConsoleTextAttribute(hConsole, color);
#endif
	printf("%s", text);
#ifdef _WIN32
	SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
#endif
}

void __print_time__()
{
#ifdef _WIN32
	// Get system time and store it in a struct
	SYSTEMTIME t;
	GetLocalTime(&t);

	/* Format time string */
	char T[] = "00:00:00.000";
	T[11] += t.wMilliseconds % 10;
	T[10] += t.wMilliseconds / 10 % 10;
	T[9] += t.wMilliseconds / 100 % 10;
	T[7] += t.wSecond % 10;
	T[6] += t.wSecond / 10 % 10;
	T[4] += t.wMinute % 10;
	T[3] += t.wMinute / 10 % 10;
	T[1] += t.wHour % 10;
	T[0] += t.wHour / 10 % 10;

	__print_value__("[" , COLOR_TIME);
	__print_value__(T, COLOR_TIME);
	__print_value__("] ", COLOR_TIME);
#endif

}

int __printf__(const char *fmt, ...)
{
	printf("");
	__print_time__();

	va_list args;
	va_start(args, fmt);

	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			char sign = *(++fmt);
			if (sign == 'd')
			{
				int number = (int)va_arg(args, int);
				std::string value = std::to_string(number);
				__print_value__(value.c_str(), COLOR_NUMBER);
			}
			else
			if (sign == 'f')
			{
				double number = (double)va_arg(args, double);
				std::string value = std::to_string(number);
				__print_value__(value.c_str(), COLOR_NUMBER);
			}
			else if (*fmt == 's')
			{
				std::string value = (std::string("'") + std::string(va_arg(args, char*)) + std::string("'")).c_str();
				__print_value__(value.c_str(), COLOR_STRING);
			}
			else
			{
				__print_value__("[Debug.cpp: format is not implemented]", COLOR_STRING);
			}
		}
		else
		{
			printf("%c", *fmt);
		}
		++fmt;
	}
	va_end(args);

	printf("\n");
	return 0;
}


std::chrono::system_clock::time_point performance::t = std::chrono::system_clock::now();

double performance::now()
{
	t = std::chrono::system_clock::now();
	double y = t.time_since_epoch().count();
	return y;
}

void performance::begin()
{
	t = std::chrono::system_clock::now();
}

double performance::end()
{
	std::chrono::duration<double> time = std::chrono::system_clock::now() - t;
	t = std::chrono::system_clock::now();
	return time.count();
}