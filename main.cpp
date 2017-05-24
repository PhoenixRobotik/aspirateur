#include "board_kiwi.h"
#include "bras.h"
#include "bumper.h"
#include "fake_remote.h"
#include "funny_action.h"
#include "pilot.h"
#include "reception.h"
#include "event.h"
#include "time_cpt.h"

#include <queue>

std::unique_ptr<BoardKiwi> kiwi = 0;


int main(int argc, char const *argv[])
{
    // init everything
    kiwi = std::make_unique<BoardKiwi>();
    auto fake_remote = std::make_shared<FakeRemote>(Pin(PortB, Pin::p3));
    TimeCpt time_server;
    Pilot pilot(fake_remote, &time_server);

    InterruptSubscriber CAN_Rx1_interrupt(&InterruptCANRx1,
        &CAN_Rx1_interrupt_handler);
    InterruptSubscriber EXTI5_to_9_interrupt(&InterruptEXTI5_to_9,
        &EXTI5_to_9_interrupt_handler);
    InterruptSubscriber EXTI10_to_15_interrupt(&InterruptEXTI10_to_15,
        &EXTI10_to_15_interrupt_handler);

    CAN_Rx1_interrupt.subscribe();
    EXTI5_to_9_interrupt.subscribe();
    EXTI10_to_15_interrupt.subscribe();

    FunnyAction funny_action;
    Bras bras2(&(kiwi->ServoBras2), true);
    Bras bras1(&(kiwi->ServoBras1), false);

    // waits for vacuum cleaner main's board initialisation
    kiwi->statusLed.set(true);
    kiwi->sleep_ms(6500);
    kiwi->statusLed.set(false);

    // attend la tirette
    while(kiwi->tirette.read() == 0);
    kiwi->activeLed.set(true);

    // just for test, TODO : remove
    // fake_remote->send_trame(FakeRemote::Trame::avant);
    //kiwi->ServoBras1.setMicrosec(400);
    //kiwi->sleep_ms(2000);
    //kiwi->ServoBras1.setMicrosec(2500);
    // funny_action.launch();
    // bras1.move(0);
    // bras2.move(0);

    std::queue<Event> events({
        Event::Move(Pilot::TargetType::distance, 1),
        Event::Move(Pilot::TargetType::angle,  360),
        Event::Move(Pilot::TargetType::distance, -1),
        Event::Move(Pilot::TargetType::angle,  -360),
    });

    Event currentEvent;
    bool end_of_event = true;


    while (true) {
        // bumper handling
        if ((kiwi->bumper1.read() == 0) or (kiwi->bumper2.read() == 0)) {
            time_server.pause();
            pilot.stop();
            bool bumper_triggered = true;
            while(bumper_triggered) {
                // debouncing
                for (int i = 0; i < 10; ++i)
                {
                    bumper_triggered = bumper_triggered or
                                    ((kiwi->bumper1.read() == 0) or (kiwi->bumper2.read() == 0));
                    kiwi->sleep_ms(1);
                }
            }
            time_server.resume();
        }

        if (end_of_event) {
            if (!events.empty()) {
                currentEvent = events.front();
                events.pop();
                end_of_event = currentEvent.execute(*kiwi, pilot, true);
            }
        }
        else {
            end_of_event = currentEvent.execute(*kiwi, pilot, false);
        }
    }


    while(1);
    return 0;
}
