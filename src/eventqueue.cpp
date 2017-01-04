
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
}

void EventQueue::Process()
{
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
