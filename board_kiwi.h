#pragma once

#include "can.h"
#include "clock.h"
#include "eeprom.h"
#include "gpio.h"
#include "pwm.h"
#include "hall.h"
#include "motor.h"
#include "definitions/interruptions.h"
#include "definitions/peripheral.h"

class BoardKiwi
: public System {
public:
    BoardKiwi()
    : System()
    , activeLed(Pin(PortF, Pin::p0), GPIO::IOMode::output)
    , statusLed(Pin(PortF, Pin::p1), GPIO::IOMode::output)
    , canBus(&periphCAN,
            Pin(PortA, Pin::p11), AltFunction::f9,
            Pin(PortA, Pin::p12), AltFunction::f9)
    , pwmServo1(&Timer3, TIM_OC3,
            Pin(PortB, Pin::p0), AltFunction::f2)
    , pwmServo2(&Timer3, TIM_OC1,
            Pin(PortA, Pin::p6), AltFunction::f2)
    // , usart1(USART1,
    //         Pin(PortB, Pin::p7),
    //         Pin(PortB, Pin::p6))
    // , usart2(USART2,
    //         Pin(PortB, Pin::p4),
    //         Pin(PortB, Pin::p3))
    { }

    GPIO activeLed, statusLed;
    CANBus canBus;
    PWM pwmServo1, pwmServo2;


    // USART usart1, usart2;
};

extern
std::unique_ptr<BoardKiwi> kiwi;
