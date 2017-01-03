
#pragma once

#include "portablility.hpp"


#include "runnable.hpp"
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

        virtual void Operator()();
        
        virtual void handle() = 0;
        virtual void SetEvent(SharedPtr<Event>);
        
    protected:
        SharedPtr<Event> mEvent;
};

class EventLoop
{
    public:
        EventLoop() {}
        virtual ~EventLoop() {}

        void Process();
        void Post(SharedPtr<Event>);

        void RegisterHandle(const std::type_index&, SharedPtr<EventHandler>);
        void UnregisterHandle(const std::type_index&);
    private:
        std::list<SharedPtr<Event> > mUndlying;
        std::map<std::type_index, SharedPtr<EventHandler> > mHandlers;

        Mutex mMutex;
};

}
