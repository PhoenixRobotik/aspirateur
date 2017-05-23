#include "bras.h"

void Bras::init() {
	you_shall_not_pass();
}

void Bras::open() {
	m_servo_pwm->setMicrosec(m_opened_position);
}

void Bras::close() {
	m_servo_pwm->setMicrosec(m_closed_position);

}

void Bras::you_shall_not_pass() {
	move(35);
}

void Bras::move(float percent) {
	if (percent > 100) {
		percent = 100;
	} else if (percent < 0) {
		percent = 0;
	}
	uint32_t position  = static_cast<uint32_t>(std::round(percent / 100 * FULL_RANGE));
	if (m_opened_position > m_closed_position) {
		position += m_closed_position;
	} else {
		position  = m_closed_position - position; 
	}

	m_servo_pwm->setMicrosec(position);
}


