
#pragma once

#include "portability.hpp"

namespace OoT
{

class Event
{
public:
    virtual ~Event() {};
    virtual void notify()
    {
        if (mNotifier)
        {
            (*mNotifier)();
        }
    }

    virtual void setNotifier(std::shared_ptr<Runnable> notifier)
    {
        mNotifier = notifier;
    }

protected:
    std::shared_ptr<Runnable> mNotifier;
};

class EventQuit : public Event
{
public:
    virtual ~EventQuit() {};
};

}
