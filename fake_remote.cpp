#include "board_kiwi.h"
#include "fake_remote.h"


void FakeRemote::init() {
    pin.port->enable();
    gpio_mode_setup(
        pin.port->Id,
        GPIO_MODE_OUTPUT,
        GPIO_PUPD_NONE,
        pin.number);
    set_gpio(IDLE_STATE);
}

void FakeRemote::set_gpio(bool on) {
    on  ? gpio_set  (pin.port->Id, pin.number)
        : gpio_clear(pin.port->Id, pin.number);
}

void FakeRemote::send_trame(Trame trame) {
    for (int i = 8; i > 0; --i)
    {
        bool state = ((trame >> (i-1)) & 0x01) == 1;

        set_gpio(false);
        kiwi->sleep_us(state ? LONG : SHORT);
        set_gpio(true);
        kiwi->sleep_us(state ? SHORT : LONG);
    }
    set_gpio(IDLE_STATE);
    kiwi->sleep_us(DEAD_TIME);
}
