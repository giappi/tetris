/* 
 * File:   Timer.h
 * Author: Giappi
 *
 * Created on 2021-01-18, 18:55
 */

#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include "com/giappi/Math.h"

//typedef void (Callback)(void);
typedef std::function<void()> Callback;
const long SECOND = 1000000000L;
const long MILISECOND = 1000000L;

class Timer
{
public:
    void clearTimeOut(UnsignedInteger timeOutId);
    void clearInterval(UnsignedInteger intervalId);
    void Update();
    Timer();
    virtual ~Timer();

    UnsignedInteger setInterval(Callback callback, UnsignedInteger timeout_ns);
    UnsignedInteger setTimeOut(Callback callback, UnsignedInteger timeout_ns);
private:
    UnsignedInteger takeThreadIdIncrement();
    UnsignedInteger setTimeOutSync(Callback callback, UnsignedInteger timeout_ns);
    UnsignedInteger setTimeOutAsync(Callback callback, UnsignedInteger timeout_ns);
    UnsignedInteger setIntervalSync(Callback callback, UnsignedInteger timeout_ns);
    UnsignedInteger setIntervalAsync(Callback callback, UnsignedInteger timeout_ns);
private:
    void* properties = 0;
    void* callbackInfoList = 0;
    void* threadList = 0;
    UnsignedInteger timerIncrement = 0;
    UnsignedInteger threadIdIncrement = 0;
};

#define TIMER (*(Singleton<Timer>::GetInstance()))

#endif /* TIMER_H */

