
#pragma once

#include "portability.hpp"

namespace OoT
{

class Event
{
public:
    virtual ~Event() {};
};

class EventQuit : public Event
{
public:
    virtual ~EventQuit() {};
};

}
