
#include "../inc/worker.hpp"


namespace OoT
{


void Worker::RegisterHandle(const std::type_index& t, std::shared_ptr<EventHandler> h)
{
    mEventQueue.RegisterHandle(t, h);
}

void Worker::UnregisterHandle(const std::type_index& t)
{
    mEventQueue.UnregisterHandle(t);
}

void run(void *p)
{
    OoT::Worker* pJob = reinterpret_cast<OoT::Worker*>(p);
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

bool Worker::isBusy() const
{
    return (1 == mBusy.load());
}

Worker::Worker() : mBusy(0)
{
    mThread = std::shared_ptr<std::thread>(new std::thread(run, this));
}

Worker::~Worker()
{
    if(mThread)
    {
        mThread.reset();
    }
}

void Worker::Quit()
{
    Post(std::shared_ptr<EventQuit>(new EventQuit()));
    if (mThread)
    {
        mThread->join();
    }
}

void Worker::Join()
{
    if(mThread)
    {
        mThread->join();
    }
}

void Worker::Post(std::shared_ptr<Event> e)
{
    std::lock_guard<std::mutex> lk(mMutex);
    mEventQueue.Post(e);
    mCondition.notify_one();
}

}
