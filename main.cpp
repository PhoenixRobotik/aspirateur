#include "board_kiwi.h"
#include "fake_remote.h"
#include "pilot.h"


std::unique_ptr<BoardKiwi> kiwi = 0;


int main(int argc, char const *argv[])
{
    kiwi = std::make_unique<BoardKiwi>();
    auto fake_remote = std::make_shared<FakeRemote>(Pin(PortB, Pin::p6));
    Pilot pilot(fake_remote);
    kiwi->statusLed.set(true);
    // waits for vacuum cleaner main's board initialisation
    kiwi->sleep_ms(6500);

    kiwi->statusLed.set(false);

    while(1)
    {
        pilot.reach(Pilot::TargetType::distance,  1);
        kiwi->sleep_ms(500);
        pilot.reach(Pilot::TargetType::angle,  360);
        kiwi->sleep_ms(500);
        pilot.reach(Pilot::TargetType::distance, -1);
        kiwi->sleep_ms(500);
        pilot.reach(Pilot::TargetType::angle,  -360);
        kiwi->sleep_ms(500);
        kiwi->activeLed.toggle();
    }
    while(1);
    return 0;
}