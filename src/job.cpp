
#include "../inc/job.hpp"

namespace OoT
{


void run(void *p)
{
    OoT::Job* pJob = reinterpret_cast<OoT::Job*>(p);
    if (!pJob)
    {
        return;
    }

    int isQuit = 0;
    std::unique_lock<std::mutex> lk(pJob->mMutex);
    while (0 == isQuit)
    {
        pJob->mCondition.wait(lk);
        pJob->mBusy.store(1);
        try
        {
            isQuit = pJob->mEventQueue.Process();
        }
        catch(std::exception &e)
        {
            //TODO:
        }
        catch(...)
        {
            //TODO:
        }
        pJob->mBusy.store(0);
    }
}

bool Job::isBusy() const
{
    return (1 == mBusy.load());
}

Job::Job() : mBusy(0)
{
    mThread = std::shared_ptr<std::thread>(new std::thread(run, this));
}

Job::~Job()
{
    if(mThread)
    {
        mThread.reset();
    }
}

void Job::Quit()
{
    Post(std::shared_ptr<EventQuit>(new EventQuit()));
    mThread->join();
}

void Job::RegisterHandle(const std::type_index& t, std::shared_ptr<EventHandler> h)
{
    mEventQueue.RegisterHandle(t, h);
}

void Job::UnregisterHandle(const std::type_index& t)
{
    mEventQueue.UnregisterHandle(t);
}

void Job::Post(std::shared_ptr<Event> e)
{
    std::lock_guard<std::mutex> lk(mMutex);
    mEventQueue.Post(e);
    mCondition.notify_one();
}

}

