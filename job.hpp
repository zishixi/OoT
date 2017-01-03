
#pragma once

#include "portablility.hpp"

#include "runnable.hpp"
#include "thread.hpp"
#include "eventloop.hpp"

namespace OoT
{

class Job : public Thread
{
    public:
        Job();
        virtual ~Job() {}
    
        void RegisterHandle(const std::type_index&, SharedPtr<EventHandler>);
        void UnregisterHandle(const std::type_index&);

        void Post(SharedPtr<Event>);
        void Run();
    private:
        EventLoop mEventLoop;
        Condition mCondition;
};

}


