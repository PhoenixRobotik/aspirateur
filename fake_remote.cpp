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

void FakeRemote::send_trame(uint8_t trame) {
    for (int i = 8; i > 0; --i)
    {
        uint8_t state = (trame >> (i-1)) & 0x01;
        set_gpio(false);
        kiwi->sleep_us(state == 1 ? LONG : SHORT);
        set_gpio(true);
        kiwi->sleep_us(state == 1 ? SHORT : LONG);
    }
    set_gpio(IDLE_STATE);
    kiwi->sleep_us(9300);
}
