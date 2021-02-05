
/*
 * File:   Debug.h
 * Author: Giappi
 *
 * Created on April 22, 2018, 9:02 PM
 */

#ifndef DEBUG_H
#define DEBUG_H
#include "_typedef.h"
#include "cpp/lang/String.h"
#include <vector>


/**
 * Debugging
 */
class Debug
{
public:

    /**
     * Same as the function printf(...)
     * @param formated the c-string that formartted. Each argument is '%d', '%f', '%s', ...
     * @param ... unlimited arguments in difference type
     */
    static void log(const char* formatted, ...);

    /**
     * Print log in console interface with formarted template string
     * @tparam Args... the types of arguments
     * @param formatted the String that formartted. Each argument is replace by template '{}'
     * @param args the arguments in difference type
     */
    template <class... Args>
    static void logf(String formatted, Args... args)
    {
        std::vector<String> arguments = {};
        argumentsToString(&arguments, args...);
        logfv(formatted, arguments);
    };

private:

    /**
     * Convert variadic arguments into a array
     * @tparam T any type
     * @tparam Args... the types of arguments
     * @param _tmp_logf_arguments an array that save converted arguments
     * @param first the current processing argument
     * @param args the arguments in difference type
     */
    template <class T, class... Args>
    static void argumentsToString(std::vector<String>* const _tmp_logf_arguments, T first, Args... args)
    {
        _tmp_logf_arguments->push_back(valueToString(first));
        argumentsToString(_tmp_logf_arguments, args...);
        return;
    }

    /**
     * the function to terminate recursive
     * @param _tmp_logf_arguments (unused)
     */
    static void argumentsToString(std::vector<String>* const _tmp_logf_arguments)
    {
        return;
    }

    /**
     * Print log in console interface with formarted template string
     * @param formatted the String that formartted. Each argument is replace by template '{}'
     * @param arguments the arguments in String
     */
    static void logfv(const String& formatted, const std::vector<String>& arguments);

public:

    static String valueToString(const boolean x);
    static String valueToString(const char x);
    static String valueToString(const int8 x);
    static String valueToString(const int32 x);
    static String valueToString(const int64 x);
    static String valueToString(const uint8 x);
    static String valueToString(const uint32 x);
    static String valueToString(const uint64 x);
    static String valueToString(const float x);
    static String valueToString(const double x);
    static String valueToString(const long double x);
    static String valueToString(const char* x);
    static String valueToString(String x);
    template <class T>
    static String valueToString(const T* x)
    {
        return valueToString((T)x);
    };

};

#endif /* DEBUG_H */

