

#include "../inc/job.hpp"

using namespace OoT;

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

class EventAddHandler : public EventHandler
{
public:

    virtual void handle()
    {
        std::shared_ptr<EventAdd> e = std::dynamic_pointer_cast<EventAdd>(mEvent);
        if (e)
        {
            EventAddHandler::sum = e->param1;

            printf("LALALA~%d\n", EventAddHandler::sum);
        }
    }

    static int sum;
};

int EventAddHandler::sum = 0;

void testJob()
{
    Job myJob;
    myJob.RegisterHandle(typeid(EventAdd), std::shared_ptr<EventHandler>(new EventAddHandler));
    for (int i = 0; i < 100; i ++)
    {
        printf("HAHAHA~%d\n", i);
        myJob.Post(std::shared_ptr<Event>(new EventAdd(i)));
    }

    myJob.Post(std::shared_ptr<Event>(new EventQuit()));

    myJob.join();
}

int main()
{
    testJob();
}
