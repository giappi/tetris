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
#include <thread>
#include "com/giappi/Debug.h"

typedef std::chrono::system_clock               SystemClock;
typedef std::chrono::system_clock::time_point   TimePoint;
typedef std::chrono::nanoseconds                NanoSecond;
typedef bool                                    Boolean;


struct CallbackInfo
{
    CallbackFunction    callback = {};
    TimePoint           timeOutPoint = TimePoint(NanoSecond(0));
    UnsignedInteger     id = 0;
    Boolean             interval = 0;
    CallbackInfo
    (
        CallbackFunction    callback,
        TimePoint           timeOutPoint,
        UnsignedInteger     id,
        UnsignedInteger     interval = 0
    ) :     callback(callback),
            timeOutPoint(timeOutPoint),
            id(id),
            interval(interval) {};
    CallbackInfo(){};
};

typedef std::map<UnsignedInteger, CallbackInfo>  MapOfCallback;
typedef std::vector<std::thread> VectorOfThread;

inline MapOfCallback& GET_CALLBACK(void* callbacks)
{
    return *((MapOfCallback*) callbacks);
}


Timer::Timer()
{
    callbackInfoList   = new MapOfCallback();
    threadList = new VectorOfThread();
    __printf__("Timer::Timer()");
}

UnsignedInteger Timer::setTimeOut(CallbackFunction callback, UnsignedInteger timeout_ns)
{
    auto t = SystemClock::now() + NanoSecond(timeout_ns);
    MapOfCallback& callbacks = GET_CALLBACK(callbackInfoList);
    callbacks[timerIncrement] = CallbackInfo(callback, t, timerIncrement);
    return timerIncrement++;
}

UnsignedInteger Timer::setInterval(CallbackFunction callback, UnsignedInteger timeout_ns)
{
    auto t = SystemClock::now() + NanoSecond(timeout_ns);
    MapOfCallback& callbacks = GET_CALLBACK(callbackInfoList);
    callbacks[timerIncrement] = CallbackInfo(callback, t, timerIncrement, timeout_ns);
    return timerIncrement++;
}

UnsignedInteger Timer::setInterval_thread(CallbackFunction callback, UnsignedInteger timeout_ns)
{
    VectorOfThread* threadList = ((VectorOfThread*) threadList);
    threadList->push_back(std::thread([callback, timeout_ns]()
    {
        while(true)
        {
            callback();
            std::this_thread::sleep_for(NanoSecond(timeout_ns));
        }
    }));
    return 199999999L;
}

UnsignedInteger Timer::setTimeOut_thread(CallbackFunction callback, UnsignedInteger timeout_ns)
{
    VectorOfThread* threadList = ((VectorOfThread*) threadList);
    threadList->push_back(std::thread([callback, timeout_ns]()
    {
        std::this_thread::sleep_for(NanoSecond(timeout_ns));
        callback();
    }));
    return 999999999L;
}



void Timer::clearTimeOut(UnsignedInteger id)
{
    MapOfCallback callback_v = GET_CALLBACK(callbackInfoList);
    callback_v.erase(id);
}


void Timer::Update()
{
    if(GET_CALLBACK(callbackInfoList).size() == 0)
    {
        return;
    }

    std::vector<UnsignedInteger> toRemove = {};

    for(auto& pair : GET_CALLBACK(callbackInfoList))
    {
        auto& callbackId     = pair.first;
        auto& callbackInfo   = pair.second;
        if(SystemClock::now() > callbackInfo.timeOutPoint)
        {
            callbackInfo.callback();
            if(callbackInfo.interval == 0)
            {
                toRemove.push_back(callbackId);
            }
            else
            {
                callbackInfo.timeOutPoint = callbackInfo.timeOutPoint + NanoSecond(callbackInfo.interval);
            }
        }
    }
    
    for(const auto& id : toRemove)
    {
        GET_CALLBACK(callbackInfoList).erase(id);
    }
}



Timer::~Timer()
{
    if(callbackInfoList)
    {
        delete ((MapOfCallback*) callbackInfoList);
        callbackInfoList = 0;
    }
}

