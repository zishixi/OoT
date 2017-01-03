
#include "portability.hpp"

#include "job.hpp"

namespace OoT
{

   
Job::Job()
{
    mThread = SharedPtr<Thread>(new Thread(Job::Run));
}

void Job::RegisterHandle(const std::type_index& t, SharedPtr<EventHandler> h)
{
    mEventLoop.RegisterHandle(t, h);
}

void Job::UnregisterHandle(const std::type_index& t)
{
    mEventLoop.UnregisterHandle(t);
}

void Job::Post(SharedPtr<Event> e)
{
    mEventLoop.Post(e);
    mCondition.notify_one();
}

void Job::Run()
{
    Mutex m;

    while(1)
    {
        mCondition.wait(m);
        mEventLoop.Process();
    }
}
}

