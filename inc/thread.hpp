
#pragma once

#include "portability.hpp"

#include "runnable.hpp"

namespace OoT
{

class Thread
{
    public:
        Thread(std::shared_ptr<Runnable> runnable);
        virtual ~Thread();

        virtual void join();

    protected:
        Thread() {}
        std::shared_ptr<Runnable> mRunnable;
        std::shared_ptr<std::thread> mThread;
};

}
