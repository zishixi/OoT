
#pragma once

#include "portability.hpp"

#include "event.hpp"
#include "eventqueue.hpp"


namespace OoT
{
    
class Worker
{
public:
    Worker();
    virtual ~Worker();
    
    virtual void RegisterHandle(const std::type_index&, std::shared_ptr<EventHandler>);
    virtual void UnregisterHandle(const std::type_index&);
    
    
    virtual void Post(std::shared_ptr<Event>);
    virtual void Quit();

    virtual void Join();
    
    bool isBusy() const;
private:
    EventQueue mEventQueue;
    std::shared_ptr<std::thread> mThread;
    std::condition_variable mCondition;
    std::mutex mMutex;

    std::atomic<int> mBusy;

    friend void run(void *p);

};

}
