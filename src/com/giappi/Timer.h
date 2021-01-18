/* 
 * File:   Timer.h
 * Author: Giappi
 *
 * Created on 2021-01-18, 18:55
 */

#ifndef TIMER_H
#define TIMER_H

#include <functional>

typedef std::function<void()> CallbackFunction;
typedef unsigned long long    UnsignedInteger;

class Timer
{
public:
    UnsignedInteger setTimeOut(CallbackFunction callback, UnsignedInteger timeout_ns);
    void clearTimeOut(UnsignedInteger timeOutId);
    void Update();
    Timer();
    virtual ~Timer();
private:
    void* callbacks = 0;
    void* timePoint = 0;
    UnsignedInteger timerIncrement = 0;
};

#define TIMER (*(Singleton<Timer>::GetInstance()))

#endif /* TIMER_H */

