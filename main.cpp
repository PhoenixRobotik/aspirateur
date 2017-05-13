#include "board_kiwi.h"
#include "fake_remote.h"


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

    while(1)
    {
        FakeRemote fake_remote(Pin(PortB, Pin::p6));
        fake_remote.send_trame(Trame::avant);
        fake_remote.send_trame(Trame::avant);
        fake_remote.send_trame(Trame::avant);
        fake_remote.send_trame(Trame::avant);
        fake_remote.send_trame(Trame::avant);
        fake_remote.send_trame(Trame::pause);
        fake_remote.send_trame(Trame::arriere);
        fake_remote.send_trame(Trame::arriere);
        fake_remote.send_trame(Trame::arriere);
        fake_remote.send_trame(Trame::arriere);
        fake_remote.send_trame(Trame::arriere);
        fake_remote.send_trame(Trame::pause);
        kiwi->statusLed.toggle();
    }
    while(1);
    return 0;
}
