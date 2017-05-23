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
    , activeLed(Pin(PortF, Pin::p0 ), GPIO::IOMode::output)
    , statusLed(Pin(PortF, Pin::p1 ), GPIO::IOMode::output)
    , tirette  (Pin(PortA, Pin::p2 ), GPIO::IOMode::input )
    , bumper1  (Pin(PortA, Pin::p10), GPIO::IOMode::input )
    , bumper2  (Pin(PortA, Pin::p9 ), GPIO::IOMode::input )
    , canBus(&periphCAN,
            Pin(PortA, Pin::p11), AltFunction::f9,
            Pin(PortA, Pin::p12), AltFunction::f9)
    , ServoBras1(&Timer3, TIM_OC3,
            Pin(PortB, Pin::p0), AltFunction::f2)
    , ServoBras2(&Timer3, TIM_OC1,
            Pin(PortA, Pin::p6), AltFunction::f2)
    // pas fonctionnel avec le TIM2 : TODO : debug
    // , ServoFunnyAction(&Timer2, TIM_OC2,
    //         Pin(PortA, Pin::p1), AltFunction::f1)
    , ServoFunnyAction(&Timer1, TIM_OC1,
            Pin(PortA, Pin::p8), AltFunction::f6)
    // , usart1(USART1,
    //         Pin(PortB, Pin::p7),
    //         Pin(PortB, Pin::p6))
    // , usart2(USART2,
    //         Pin(PortB, Pin::p4),
    //         Pin(PortB, Pin::p3))
    { }

    GPIO activeLed, statusLed;
    GPIO tirette, bumper1, bumper2;
    CANBus canBus;
    PWM ServoBras1, ServoBras2, ServoFunnyAction;


    // USART usart1, usart2;
};

extern
std::unique_ptr<BoardKiwi> kiwi;
