/* 
 * File:   Timer.cpp
 * Author: Giappi
 * 
 * Created on 2021-01-18, 18:55
 */

#include "Timer.h"
#include "com/giappi/Debug.h"
#include <vector>
#include <chrono>
#include <map>
#include <thread>
#include <functional>
#include <condition_variable>


typedef std::chrono::system_clock               SystemClock;
typedef std::chrono::system_clock::time_point   TimePoint;
typedef std::chrono::nanoseconds                NanoSecond;
typedef bool                                    Boolean;
typedef std::function<void()>                   CallbackFunction;
typedef std::thread                             Thread;


struct CallbackInfo
{
    CallbackFunction    callback = {};
    TimePoint           timeOutPoint = TimePoint(NanoSecond(0));
    Boolean             interval = 0;
    CallbackInfo
    (
        CallbackFunction    callback,
        TimePoint           timeOutPoint,
        UnsignedInteger     interval = 0
    ) :     callback(callback),
            timeOutPoint(timeOutPoint),
            interval(interval) {};
    CallbackInfo(){};
};

typedef std::map<UnsignedInteger, CallbackInfo>  MapOfCallback;

struct ThreadInfo
{
    Thread          thread;
    Boolean         isRunning = true;
    ThreadInfo():isRunning(true){};
};

typedef std::map<UnsignedInteger, ThreadInfo>  MapOfThread;

inline MapOfCallback&   GET_CALLBACK(void* callbacks)
{
    return *((MapOfCallback*) callbacks);
}

inline MapOfThread&     GET_THREAD(void* threadMap)
{
    return *((MapOfThread*) threadMap);
}


Timer::Timer()
{
    callbackInfoList    = new MapOfCallback();
    threadList          = new MapOfThread();
    __printf__("Timer::Timer()");
}

UnsignedInteger Timer::setTimeOutSync(Callback callback, UnsignedInteger timeout_ns)
{
    auto t = SystemClock::now() + NanoSecond(timeout_ns);
    MapOfCallback& callbacks = GET_CALLBACK(callbackInfoList);
    callbacks[timerIncrement] = CallbackInfo(callback, t);
    return timerIncrement++;
}

UnsignedInteger Timer::setIntervalSync(Callback callback, UnsignedInteger timeout_ns)
{
    auto t = SystemClock::now() + NanoSecond(timeout_ns);
    MapOfCallback& callbacks = GET_CALLBACK(callbackInfoList);
    callbacks[timerIncrement] = CallbackInfo(callback, t, timeout_ns);
    return timerIncrement++;
}

UnsignedInteger Timer::setInterval(Callback callback, UnsignedInteger timeout_ns)
{
    MapOfThread& threads = GET_THREAD(threadList);
    UnsignedInteger threadId = takeThreadIdIncrement();
    threads[threadId] = ThreadInfo();
    const bool& isRunning = threads[threadId].isRunning;
    threads[threadId].thread = Thread([callback, timeout_ns, &isRunning]()
    {
        while(isRunning)
        {
            TimePoint timeNext  = SystemClock::now() + NanoSecond(timeout_ns);
            callback();
            // sleep util next interval
            std::this_thread::sleep_until(timeNext);
        }
    });
    return threadId;
}

UnsignedInteger Timer::setTimeOut(Callback callback, UnsignedInteger timeout_ns)
{
    MapOfThread& threads = GET_THREAD(threadList);
    UnsignedInteger threadId = takeThreadIdIncrement();
    threads[threadId] = ThreadInfo();
    threads[threadId].thread = Thread([callback, timeout_ns]()
    {
        std::this_thread::sleep_for(NanoSecond(timeout_ns));
        callback();
    });
    return threadId;
}



void Timer::clearTimeOut(UnsignedInteger id)
{
    MapOfThread& threads = GET_THREAD(threadList);
    threads[id].isRunning = false;
    threads[id].thread.join();
}

void Timer::clearInterval(UnsignedInteger id)
{
    return clearTimeOut(id);
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

std::mutex mutexThreadIdIncrement;
UnsignedInteger Timer::takeThreadIdIncrement()
{
    std::lock_guard<std::mutex> autoLock(mutexThreadIdIncrement);
    ++threadIdIncrement;
    return threadIdIncrement;
}



Timer::~Timer()
{
    if(callbackInfoList)
    {
        delete ((MapOfCallback*) callbackInfoList);
        callbackInfoList = 0;
    }
    if(threadList)
    {
        MapOfThread& threads = GET_THREAD(threadList);
        // stop all thread
        for(auto& pair : threads)
        {
            pair.second.isRunning = false;
            if(pair.second.thread.joinable())
            {
                pair.second.thread.join();
            }
        }
        delete ((MapOfThread*) threadList);
        threadList = 0;
    }
    
}

