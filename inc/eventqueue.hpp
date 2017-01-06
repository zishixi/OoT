
#pragma once

#include "portability.hpp"


#include "../inc/runnable.hpp"
#include "event.hpp"

#include <list>
#include <map>
#include <typeinfo>
#include <typeindex>

namespace OoT
{

class EventHandler : public Runnable
{
public:
    EventHandler() {}
    virtual ~EventHandler() {}

    virtual void operator()();
    
    virtual void handle() = 0;
    
protected:
    virtual void setEvent(std::shared_ptr<Event>);
    virtual std::shared_ptr<Event> getEvent();
    
    virtual void setWorker(std::shared_ptr<Worker>);
    virtual std::shared_ptr<Worker> getWorker();

private:
    std::shared_ptr<Event> mEvent;
    std::shared_ptr<Worker> mWorker;

    friend class EventQueue;
    friend class Worker;
};

class EventQueue
{
public:
    EventQueue() {}
    virtual ~EventQueue();

    int process();

    void post(std::shared_ptr<Event>);

    void registerHandle(const std::type_index&, std::shared_ptr<EventHandler>);
    void unregisterHandle(const std::type_index&);
private:

    std::shared_ptr<Event> getEvent();
    std::list<std::shared_ptr<Event> > mUndlying;
    std::map<std::type_index, std::shared_ptr<EventHandler> > mHandlers;

    std::mutex mMutex;
};

}
