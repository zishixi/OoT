
#include "../inc/eventqueue.hpp"

namespace OoT
{
    
void EventHandler::SetEvent(std::shared_ptr<Event> e)
{
    mEvent = e;
}

void EventHandler::operator()()
{
    handle();
    if (mEvent)
    {
        mEvent->notify();
    }
}

EventQueue::~EventQueue()
{
    std::unique_lock<std::mutex> lk(mMutex);
    mUndlying.clear();
    mHandlers.clear();;
}

int EventQueue::Process()
{
    int isQuit = 0;
    std::unique_lock<std::mutex> lk(mMutex);
    
    while(!mUndlying.empty())
    {
        std::shared_ptr<Event> e = mUndlying.front();

        mUndlying.pop_front();
        
        if (!e)
        {
            /// empty event
            continue;
        }

        if (typeid(*e) == typeid(EventQuit))
        {
            printf("~~~\n");
            lk.unlock();
            isQuit = 1;
            break;
        }
        
        if (mHandlers.find(std::type_index(std::type_index(typeid(*e)))) == mHandlers.end())
        {
            /// no handler
            continue;
        }

        std::shared_ptr<EventHandler> h = mHandlers[std::type_index(typeid(*e))];

        if (h)
        {
            h->SetEvent(e);
            (*h)();
        }
    }

    return isQuit;
}

void EventQueue::Post(std::shared_ptr<Event> e)
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

void EventQueue::RegisterHandle(const std::type_index& t, std::shared_ptr<EventHandler> h)
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

void EventQueue::UnregisterHandle(const std::type_index& t)
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
