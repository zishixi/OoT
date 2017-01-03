
#include "../inc/eventloop.hpp"

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

void EventLoop::Process()
{
    std::unique_lock<std::mutex> lk(mMutex);
    
    if (mUndlying.empty())
    {
        //TODO: 
        return;
    }
    
    std::shared_ptr<Event> e = mUndlying.front();

    mUndlying.pop_front();
    
    if (!e)
    {

        //TODO: 
        return;
    }

    if (mHandlers.find(std::type_index(std::type_index(typeid(*e)))) == mHandlers.end())
    {
        //TODO: 
        return;
    }

    std::shared_ptr<EventHandler> h = mHandlers[std::type_index(typeid(*e))];

    if (h)
    {

        h->SetEvent(e);
        (*h)();
    }
}

void EventLoop::Post(std::shared_ptr<Event> e)
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

void EventLoop::RegisterHandle(const std::type_index& t, std::shared_ptr<EventHandler> h)
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

void EventLoop::UnregisterHandle(const std::type_index& t)
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
