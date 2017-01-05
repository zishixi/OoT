
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
    virtual void SetEvent(std::shared_ptr<Event>);
    std::shared_ptr<Event> mEvent;

    friend class EventQueue;
};

class EventQueue
{
public:
    EventQueue() {}
    virtual ~EventQueue();

    int Process();

    void Post(std::shared_ptr<Event>);

    void RegisterHandle(const std::type_index&, std::shared_ptr<EventHandler>);
    void UnregisterHandle(const std::type_index&);
private:
    std::list<std::shared_ptr<Event> > mUndlying;
    std::map<std::type_index, std::shared_ptr<EventHandler> > mHandlers;

    std::mutex mMutex;
};

}
