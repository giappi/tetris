/* 
 * File:   Timer.cpp
 * Author: Giappi
 * 
 * Created on 2021-01-18, 18:55
 */

#include "Timer.h"
#include <vector>
#include <chrono>
#include <map>
#include <cstdio>

typedef std::chrono::system_clock               SystemClock;
typedef std::chrono::system_clock::time_point   TimePoint;
typedef std::chrono::nanoseconds                NanoSecond;


struct CallbackInfo
{
    CallbackFunction    callback;
    TimePoint           timeOutPoint;
    UnsignedInteger     id;
    CallbackInfo
    (
        CallbackFunction    callback,
        TimePoint           timeOutPoint,
        UnsignedInteger     id
    ): callback(callback), timeOutPoint(timeOutPoint), id(id) {};
    CallbackInfo(){};
};

typedef std::map<UnsignedInteger, CallbackInfo>  MapOfCallback;

inline MapOfCallback& GET_CALLBACK(void* callbacks)
{
    return *((MapOfCallback*) callbacks);
}


Timer::Timer()
{
    callbacks   = new MapOfCallback();
    timePoint   = new TimePoint(SystemClock::now());
}

UnsignedInteger Timer::setTimeOut(CallbackFunction callback, UnsignedInteger timeout_ns)
{
    MapOfCallback& callback_v = GET_CALLBACK(callbacks);
    auto t = SystemClock::now() + NanoSecond(timeout_ns);
    callback_v[timerIncrement] = CallbackInfo(callback, t, timerIncrement);
    int a = 0;
    return timerIncrement++;
}

void Timer::clearTimeOut(UnsignedInteger id)
{
    MapOfCallback callback_v = GET_CALLBACK(callbacks);
    callback_v.erase(id);
}


void Timer::Update()
{
    if(GET_CALLBACK(callbacks).size() == 0)
    {
        return;
    }

    std::vector<UnsignedInteger> toRemove = {};

    for(const auto& pair : GET_CALLBACK(callbacks))
    {
        auto callbackId     = pair.first;
        auto callbackInfo   = pair.second;
        if(SystemClock::now() > callbackInfo.timeOutPoint)
        {
            callbackInfo.callback();
            toRemove.push_back(callbackId);
        }
    }
    
    for(const auto& id : toRemove)
    {
        GET_CALLBACK(callbacks).erase(id);
    }
}



Timer::~Timer()
{
    if(callbacks)
    {
        delete ((MapOfCallback*) callbacks);
        callbacks = 0;
    }
}

