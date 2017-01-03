

#include "job.hpp"

using namespace OoT;

class EventAdd
{
    public:
        EventAdd(int x)
        {
            param1 = x);
        }
        int param1;
};

class EventAddHandler : public EventHandler
{
    public:
        virtual void handle()
        {
            SharedPtr<EventAdd> e = std::dynamic_pointer_cast<EventAdd>(mEvent);
            if (e)
            {
                EventAddHandler::sum += e.param1;

                printf("LALALA~%d\n", EventAddHandler::sum);
            }
        }

        static int sum;
}

int EventAddHandler::sum = 0;

void testJob()
{
    Job myJob;
    myJob.RegisterHandle(typeid(EventAdd), SharedPtr<EventHandler>(new EventAddHandler));
    for (int i = 0; i < 100; i ++)
    {
        myJob.Post(SharedPtr<Event>(new EventAdd(i));
    }

    myJob.join();
}

int main()
{
    testJob();
}
