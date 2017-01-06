
#include "../inc/eventqueue.hpp"

namespace OoT
{
        
void EventHandler::setEvent(std::shared_ptr<Event> e)
{
    mEvent = e;
}

void EventHandler::setWorker(std::shared_ptr<Worker> worker)
{
    mWorker = worker;
}    

std::shared_ptr<Event> EventHandler::getEvent()
{
    return mEvent;
}

std::shared_ptr<Worker> EventHandler::getWorker()
{
    return mWorker;
}


void EventHandler::operator()()
{
    handle();
}

EventQueue::~EventQueue()
{
    std::unique_lock<std::mutex> lk(mMutex);
    mUndlying.clear();
    mHandlers.clear();
}

std::shared_ptr<Event> EventQueue::getEvent()
{
    std::shared_ptr<Event> e;

    std::unique_lock<std::mutex> lk(mMutex);
    if (!mUndlying.empty())
    {
        e = mUndlying.front();
        mUndlying.pop_front();
    }
    lk.unlock();

    return e;
}

int EventQueue::process()
{
    int isQuit = 0;
    
    std::shared_ptr<Event> e = getEvent();

    while (e)
    {
        if (mHandlers.find(std::type_index(std::type_index(typeid(*e)))) != mHandlers.end())
        {
            std::shared_ptr<EventHandler> h = mHandlers[std::type_index(typeid(*e))];

            if (h)
            {
                h->setEvent(e);
                (*h)();
            }
        }
        
        if (typeid(*e) == typeid(EventQuit))
        {
            isQuit = 1;
            e.reset();
        }
        else
        {
            e = getEvent();
        }
        
    }

    return isQuit;
}

void EventQueue::post(std::shared_ptr<Event> e)
{
    std::unique_lock<std::mutex> lk(mMutex);
    
    if(e)
    {
        mUndlying.push_back(e);
    }
    else
    {
        //TODO: 
    }
}

void EventQueue::registerHandle(const std::type_index& t, std::shared_ptr<EventHandler> h)
{
    std::unique_lock<std::mutex> lk(mMutex);
    
    if (mHandlers.find(t) == mHandlers.end())
    {
        mHandlers.insert(std::make_pair(t, h));
    }
    else
    {
        //TODO: 
    }
}

void EventQueue::unregisterHandle(const std::type_index& t)
{
    std::unique_lock<std::mutex> lk(mMutex);
    
    if (mHandlers.find(t) != mHandlers.end())
    {
        mHandlers.erase(t);
    }
    else
    {
        //TODO: 
    }
}


}
