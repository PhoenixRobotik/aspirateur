#pragma once

#include "definitions/gpio_cpp.h"

#include <stdint.h>

static const int IDLE_STATE = 1;
static const int UNIT       = 330;
static const int SHORT      = UNIT * 2;
static const int LONG       = UNIT * 9;
static const int DEAD_TIME  = 9300;
static const int TRAME_TIME = (SHORT + LONG) * 8;


class FakeRemote {
public:
    FakeRemote(Pin _pin)
    : pin (_pin)
    {
        init();
    }
    ~FakeRemote() { }

    enum Trame {
        droite  = 0x81,
        avant   = 0x82,
        speed   = 0x83,
        gauche  = 0x84,
        UV      = 0x85,
        on_off  = 0x86, 
        loop    = 0x87, 
        arriere = 0x88,
        spot    = 0x89,
        docking = 0x8A,
        _auto   = 0x8C,
        pause   = 0x8D,
    };

    void init();
    void send_trame(Trame trame);

private:
    const Pin  pin;
    
    void set_gpio(bool on);
};
