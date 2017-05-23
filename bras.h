#pragma once

#include "pwm.h"

#include <stdint.h>
#include <cmath>

static const uint32_t SERVO_ABSOLUTE_MIN  (400);
static const uint32_t SERVO_ABSOLUTE_MAX (2500);

static const uint32_t MAX_POS_1  (500);
static const uint32_t MAX_POS_2 (2400);

static const uint32_t FULL_RANGE (MAX_POS_2-MAX_POS_1);


class Bras {
public:
    Bras(PWM* _servo_pwm, bool mirrored)
    : m_servo_pwm (_servo_pwm)
    , m_opened_position (mirrored ? MAX_POS_1 : MAX_POS_2)
    , m_closed_position (mirrored ? MAX_POS_2 : MAX_POS_1)
    {
        init();
    }
    ~Bras() { }

    void init();
    void open();
    void close();
    void you_shall_not_pass();
    // 100% : totaly opened
    void move(float percent);

private:
	PWM* m_servo_pwm;
	const uint32_t m_opened_position;
	const uint32_t m_closed_position;
};
