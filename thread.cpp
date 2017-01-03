
#include "thread.hpp"

namespace OoT
{
Thread::Thread(SharedPtr<Runnable> runnable)
{
    if (runnable)
    {
        mThread = SharedPtr<StdThread>(new StdThread(*runnable));
        mRunnable.reset(runnable);
    }
    else
    {
        mThread = SharedPtr<StdThread>(new StdThread());
    }
}

Thread::~Thread()
{
    if(mThread)
    {
        mThread->detach();
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
