
#pragma once

#include "portablility.hpp"

namespace OoT
{

class Event
{
    public:
        virtual ~Event() = 0;
};

class EventQuit : public Event
{
    public:
        virtual ~Event() {};
}

}
