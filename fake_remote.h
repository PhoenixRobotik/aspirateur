#pragma once

#include "definitions/gpio_cpp.h"

#include <stdint.h>

#define IDLE_STATE (1)
#define UNIT       (330)
#define SHORT      (UNIT*2)
#define LONG       (UNIT*9)
#define DEAD_TIME  (9300)
#define TRAME_TIME ((SHORT+LONG)*8)


class FakeRemote {
public:
    FakeRemote(Pin _pin)
    : pin (_pin)
    {
        init();
    }
    ~FakeRemote() { }

    typedef enum Trame {
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
    } trame_t;

    void init();
    void send_trame(trame_t trame);

private:
    const Pin  pin;
    
    void set_gpio(bool on);
};
