
#pragma once

#include "portability.hpp"

#include "event.hpp"
#include "eventqueue.hpp"


namespace OoT
{
    
class Worker : public std::enable_shared_from_this<Worker>
{
public:
    Worker(std::string name);
    virtual ~Worker();
    
    virtual void registerHandle(const std::type_index&, std::shared_ptr<EventHandler>);
    virtual void unregisterHandle(const std::type_index&);

    virtual const std::string& getName() const;
    
    virtual void post(std::shared_ptr<Event>);
    virtual void quit();

    virtual void join();
    
    bool isBusy() const;
private:
    Worker();
    EventQueue mEventQueue;
    std::shared_ptr<std::thread> mThread;
    std::condition_variable mCondition;
    std::mutex mMutex;

    std::atomic<int> mBusy;

    std::string mName;
    friend void run(void *p);

};

}
