#include "board_kiwi.h"
#include "fake_remote.h"
#include "pilot.h"
#include "reception.h"
#include "event.h"

#include <queue>

std::unique_ptr<BoardKiwi> kiwi = 0;


int main(int argc, char const *argv[])
{
    kiwi = std::make_unique<BoardKiwi>();
    auto fake_remote = std::make_shared<FakeRemote>(Pin(PortB, Pin::p3));
    Pilot pilot(fake_remote);
    kiwi->statusLed.set(true);


    InterruptSubscriber CAN_Rx1_interrupt(&InterruptCANRx1,
        &CAN_Rx1_interrupt_handler);

    CAN_Rx1_interrupt.provider->setPriority(0);
    CAN_Rx1_interrupt.subscribe();
    
    // waits for vacuum cleaner main's board initialisation
    kiwi->sleep_ms(6500);

    kiwi->statusLed.set(false);

    std::queue<Event> events({
        Event::Move(Pilot::TargetType::distance, 1),
        Event::Move(Pilot::TargetType::angle,  360),
        Event::Move(Pilot::TargetType::distance, -1),
        Event::Move(Pilot::TargetType::angle,  -360),
    });

    Event currentEvent;
    bool needsReexecute = false;

    while (true) {
        // Handle interrupts here

        if (needsReexecute)
            needsReexecute = currentEvent.execute(*kiwi, pilot);
        else if (!events.empty()) {
            currentEvent = events.back();
            events.pop();
        }
    }


    while(1);
    return 0;
}
