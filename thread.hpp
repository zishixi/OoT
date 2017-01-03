
#pragma once

#include "portablility.hpp"

#include "runnable.hpp"

namespace OoT
{

class Thread
{
    public:
        Thread(SharedPtr<Runnable> runnable);
        virtual ~Thread();

        virtual void join();

    private:
        Thread() {}
        SharedPtr<Runnable> mRunnable;
        SharedPtr<StdThread> mThread;
};

}
