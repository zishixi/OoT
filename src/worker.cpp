
#include "../inc/worker.hpp"


namespace OoT
{


void Worker::registerHandle(const std::type_index& t, std::shared_ptr<EventHandler> h)
{
    if(h)
    {
        h->setWorker(shared_from_this());
    }
    mEventQueue.registerHandle(t, h);
}

void Worker::unregisterHandle(const std::type_index& t)
{
    mEventQueue.unregisterHandle(t);
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
            isQuit = pJob->mEventQueue.process();
        }
        catch(std::exception &e)
        {
            (e);
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

Worker::Worker(std::string name) : mBusy(0), mName(name)
{
    mThread = std::shared_ptr<std::thread>(new std::thread(run, this));
}

Worker::~Worker()
{
    if(mThread)
    {
        mThread->detach();
        mThread.reset();
    }
}

void Worker::quit()
{
    post(std::shared_ptr<EventQuit>(new EventQuit()));
}

void Worker::join()
{
    if(mThread)
    {
        mThread->join();
    }
}

void Worker::post(std::shared_ptr<Event> e)
{
    mEventQueue.post(e);
    mCondition.notify_one();
}

const std::string& Worker::getName() const
{
    return mName;
}

}
