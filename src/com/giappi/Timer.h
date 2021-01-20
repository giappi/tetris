/* 
 * File:   Timer.h
 * Author: Giappi
 *
 * Created on 2021-01-18, 18:55
 */

#ifndef TIMER_H
#define TIMER_H

#include <functional>

//typedef void (Callback)(void);
typedef std::function<void()> Callback;
typedef unsigned long long    UnsignedInteger;
const long SECOND = 1000000000L;
const long MILISECOND = 1000000L;

class Timer
{
public:
    UnsignedInteger setTimeOutSync(Callback callback, UnsignedInteger timeout_ns);
    UnsignedInteger setIntervalSync(Callback callback, UnsignedInteger timeout_ns);
    void clearTimeOut(UnsignedInteger timeOutId);
    void clearInterval(UnsignedInteger intervalId);
    void Update();
    Timer();
    virtual ~Timer();

    UnsignedInteger setInterval(Callback callback, UnsignedInteger timeout_ns);
    UnsignedInteger setTimeOut(Callback callback, UnsignedInteger timeout_ns);
private:
    UnsignedInteger takeThreadIdIncrement();
private:
    void* properties = 0;
    void* callbackInfoList = 0;
    void* threadList = 0;
    UnsignedInteger timerIncrement = 0;
    UnsignedInteger threadIdIncrement = 0;
};

#define TIMER (*(Singleton<Timer>::GetInstance()))

#endif /* TIMER_H */

