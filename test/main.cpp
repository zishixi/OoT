
#include <vector>
#include <sstream>

#include "../inc/worker.hpp"

using namespace OoT;

std::atomic<int> g_sum(0);

class EventQuitHandler : public EventHandler
{
public:
    virtual void handle()
    {
        printf("%s quit\n", getWorker()->getName().c_str());
    }
};

class EventAdd : public Event
{
public:
    EventAdd(int x)
    {
        param1 = x;
    }
    virtual ~EventAdd() {}
    int param1;
};

class Boss : public Worker
{
public:
    Boss() :Worker(std::string("Boss")) {}
    virtual void addEmployee(std::shared_ptr<Worker> e)
    {
        printf("%s employ %s\n", getName().c_str(), e->getName().c_str());
        mEmployees.push_back(e);
    }

    virtual void fireAll()
    {
        for (std::vector<std::shared_ptr<Worker> >::iterator it = mEmployees.begin(); it != mEmployees.end(); ++it)
        {
            if (*it)
            {
                printf("%s fire %s\n", getName().c_str(), (*it)->getName().c_str());
                (*it)->quit();
                (*it)->join();
            }
        }

        mEmployees.clear();
    }
    std::vector<std::shared_ptr<Worker> > mEmployees;
};

class EventAddResponse : public Event
{
};

class EventAddResponseHandler : public EventHandler
{
public:
    virtual void handle()
    {
        printf("%s get response %d\n", getWorker()->getName().c_str(), g_sum.load());

        std::shared_ptr<class Boss> boss = std::dynamic_pointer_cast<class Boss>(getWorker());
        if (boss)
        {
            if (g_sum == 10)
            {
                boss->fireAll();
                boss->quit();
            }
        }
    }
};

class EventAddHandler : public EventHandler
{
public:

    virtual void handle()
    {
        std::shared_ptr<EventAdd> e = std::dynamic_pointer_cast<EventAdd>(getEvent());
        if (e)
        {
            g_sum += e->param1;

            std::shared_ptr<Worker> receiver = e->getReceiver();
        
            printf("%s add %d\n", getWorker()->getName().c_str(), g_sum.load());
            
            if (receiver)
            {
                printf("%s post %s\n", getWorker()->getName().c_str(), typeid(EventAddResponse).name());
                receiver->post(std::shared_ptr<Event>(new EventAddResponse()));
            }
        }
    }

};


class EventBossStart : public Event
{
};

class EventBossStartHandler : public EventHandler
{
public:
    virtual void handle()
    {
        std::shared_ptr<EventBossStart> e = std::dynamic_pointer_cast<EventBossStart>(getEvent());
        if (e)
        {
            std::shared_ptr<Boss> boss = std::dynamic_pointer_cast<Boss>(getWorker());
            if (boss)
            {
                printf("%s start\n", boss->getName().c_str());
                std::vector<std::shared_ptr<Worker> >::iterator it;
                for (it = boss->mEmployees.begin(); it != boss->mEmployees.end(); ++it)
                {
                    if (*it)
                    {
                        EventAdd *pe = new EventAdd(1);
                        pe->setReceiver(boss);
                        (*it)->post(std::shared_ptr<EventAdd>(pe));
                    }
                }
            }
        }
    }

};

void testJob()
{
    std::shared_ptr<Boss> boss = std::shared_ptr<Boss>(new Boss());
    boss->registerHandle(typeid(EventBossStart),std::shared_ptr<EventHandler>(new EventBossStartHandler()));
    boss->registerHandle(typeid(EventAddResponse),std::shared_ptr<EventHandler>(new EventAddResponseHandler()));
    boss->registerHandle(typeid(EventQuit),std::shared_ptr<EventHandler>(new EventQuitHandler()));

    for (int i = 0; i < 10; i ++)
    {
        std::stringstream oss;
        oss << "Employee"<<char('A'+i);
        std::shared_ptr<Worker> worker = std::shared_ptr<Worker>(new Worker(oss.str()));
        worker->registerHandle(typeid(EventAdd), std::shared_ptr<EventHandler>(new EventAddHandler()));
        worker->registerHandle(typeid(EventQuit),std::shared_ptr<EventHandler>(new EventQuitHandler()));
        
        boss->addEmployee(worker);
    }

    boss->post(std::shared_ptr<Event>(new EventBossStart()));
    boss->join();
}

int main()
{
    testJob();
}
