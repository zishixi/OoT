
#pragma once

#include "portability.hpp"

namespace OoT
{

class Event
{
public:
    virtual ~Event() {};

    virtual std::shared_ptr<class Worker> getReceiver() { return mReceiver; }
    virtual void setReceiver(std::shared_ptr<class Worker> r) { mReceiver = r; }
protected:
    std::shared_ptr<class Worker> mReceiver;
};

class EventQuit : public Event
{
public:
    virtual ~EventQuit() {};
};

}
