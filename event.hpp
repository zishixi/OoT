
#pragma once

#include "portabilility.hpp"

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
