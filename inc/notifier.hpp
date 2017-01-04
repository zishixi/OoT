#pragma once

#include "portability.hpp"
#include "runnable.hpp"

namespace OoT
{

class Notifier : public Runnable
{
public:
    Notifier();
    virtual ~Notifier();

    virtual operator()();

private:
    std::shared_ptr<Job> mReceiver;
    //TODO:
};
}
