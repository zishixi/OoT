
#pragma once

#include "portability.hpp"

#include "runnable.hpp"
#include "eventqueue.hpp"
#include "thread.hpp"

namespace OoT
{

class Job : public Thread
{
    public:
        Job();
        virtual ~Job() {}
    
        void RegisterHandle(const std::type_index&, std::shared_ptr<EventHandler>);
        void UnregisterHandle(const std::type_index&);

        void Post(std::shared_ptr<Event>);
    private:
        EventQueue mEventQueue;
        std::condition_variable mCondition;
        std::mutex mMutex;

        friend void run(void *p);
};

}


