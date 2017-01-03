
#include "portability.hpp"

#include "eventloop.hpp"

namespace OoT
{
    
void EventHandler::SetEvent(SharedPtr<Event> e)
{
    mEvent = e;
}

void EventHandler::Operator()()
{
    handler();
}

void EventLoop::Process()
{
    UniqueLock<Mutex> lk(mMutex);
    
    if (mUndlying.empty())
    {
        //TODO: 
        return;
    }
    
    SharedPtr<Event> e = mUndlying.front();
    mUndlying.pop_front();
    
    if (!e)
    {
        //TODO: 
        return;
    }

    if (mHandlers.find(typeid(*e)) = mHandlers.end())
    {
        //TODO: 
        return;
    }

    SharedPtr<EventHandler> h = mHandlers[typeid(*e)];

    if (h)
    {
        h->SetEvent(e);
        (*h)();
    }
}

void EventLoop::Post(SharedPtr<Event> e)
{
    UniqueLock<Mutex> lk(mMutex);
    
    if(e)
    {
        mUndlying.push_back(e);
    }
    else
    {
        //TODO: 
    }
}

void EventLoop::RegisterHandle(const std::type_index& t, SharedPtr<EventHandler> h)
{   
    UniqueLock<Mutex> lk(mMutex);
    
    if (mHandlers.find(t.type_index) == mHandlers.end())
    {
        mHandlers.insert(std::make_pair(t, h));
    }
    else
    {
        //TODO: 
    }
}

void EventLoop::UnregisterHandle(const std::type_index& t)
{
    UniqueLock<Mutex> lk(mMutex);
    
    if (mHandlers.find(t.type_index) != mHandlers.end())
    {
        mHandlers.earse(t.type_index);
    }
    else
    {
        //TODO: 
    }
}


}
