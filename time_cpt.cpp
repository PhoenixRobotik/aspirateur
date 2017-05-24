#include "board_kiwi.h"

#include "config_macros.h"

#include "time_cpt.h"

void TimeCpt::reset() {
	m_substract_time = kiwi->getSysTick();
	m_paused = false;
}

void TimeCpt::pause() {
	if (not m_paused) {
		m_pause_time = kiwi->getSysTick();
		m_paused = true;
	}
}

void TimeCpt::resume() {
	if (m_paused) {
		m_substract_time += kiwi->getSysTick() - m_pause_time;
		m_paused = false;
	}	
}

int32_t TimeCpt::get_us() {
	if (m_paused) {
		return SYSTICK_TO_MICROS(m_pause_time - m_substract_time);
	} else {
		return SYSTICK_TO_MICROS(kiwi->getSysTick() - m_substract_time);
	}
}

bool TimeCpt::is_paused()
{
	return m_paused;
}

bool TimeCpt::is_running()
{
	return not m_paused;
}
