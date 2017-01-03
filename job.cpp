
#include "job.hpp"

namespace OoT
{

   
Job::Job()
{
    mThread = std::shared_ptr<std::thread>(new std::thread(run, this));
}

void Job::RegisterHandle(const std::type_index& t, std::shared_ptr<EventHandler> h)
{
    mEventLoop.RegisterHandle(t, h);
}

void Job::UnregisterHandle(const std::type_index& t)
{
    mEventLoop.UnregisterHandle(t);
}

void Job::Post(std::shared_ptr<Event> e)
{
    mEventLoop.Post(e);
    mCondition.notify_one();
}

void run(void *p)
{
    OoT::Job* pJob = reinterpret_cast<OoT::Job*>(p);
    if (!pJob)
    {
        return;
    }
    std::unique_lock<std::mutex> lk(pJob->mMutex);
    while (1)
    {
        pJob->mCondition.wait(lk);
        pJob->mEventLoop.Process();
    }
}
}

