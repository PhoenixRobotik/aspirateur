#include "board_kiwi.h"
#include "fake_remote.h"
#include "pilot.h"


std::unique_ptr<BoardKiwi> kiwi = 0;


extern "C" {
    // LibOpenCm3 export
    void sys_tick_handler() {
        if (kiwi)
            kiwi->systick_count++;
    }

    int get_systick() {
        return kiwi
            ? kiwi->getSysTick()
            : 0;
    }

    void delay_ms(unsigned int ms) {
        if (kiwi)
            kiwi->sleep_ms(ms);
    }
}

int main(int argc, char const *argv[])
{
    kiwi = std::make_unique<BoardKiwi>();
    auto fake_remote = std::make_shared<FakeRemote>(Pin(PortB, Pin::p6));
    Pilot pilot(fake_remote);

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
        // fake_remote->send_trame(FakeRemote::Trame::avant);
        // fake_remote->send_trame(FakeRemote::Trame::avant);
        // fake_remote->send_trame(FakeRemote::Trame::avant);
        // fake_remote->send_trame(FakeRemote::Trame::avant);
        // fake_remote->send_trame(FakeRemote::Trame::avant);
        // fake_remote->send_trame(FakeRemote::Trame::pause);
        // fake_remote->send_trame(FakeRemote::Trame::arriere);
        // fake_remote->send_trame(FakeRemote::Trame::arriere);
        // fake_remote->send_trame(FakeRemote::Trame::arriere);
        // fake_remote->send_trame(FakeRemote::Trame::arriere);
        // fake_remote->send_trame(FakeRemote::Trame::arriere);
        // fake_remote->send_trame(FakeRemote::Trame::pause);
        kiwi->statusLed.toggle();
    }
    while(1);
    return 0;
}
