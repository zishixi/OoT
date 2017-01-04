
#include "../inc/thread.hpp"

namespace OoT
{
Thread::Thread(std::shared_ptr<Runnable> runnable)
{
    if (runnable)
    {
        mThread = std::shared_ptr<std::thread>(new std::thread(*runnable));
        mRunnable = runnable;
    }
    else
    {
        mThread = std::shared_ptr<std::thread>(new std::thread());
    }
}

Thread::~Thread()
{
    if(mThread)
    {
        mThread.reset();
    }

    if (mRunnable)
    {
        mRunnable.reset();
    }
}

void Thread::join()
{
    if (mThread)
    {
        mThread->join();
    }
}

}
