#include "board_kiwi.h"

#include "time_cpt.h"

void TimeCpt::reset() {
	m_substract_time = kiwi->getSysTick();
	m_paused = false;
}

void TimeCpt::pause() {
	m_pause_time = kiwi->getSysTick();
	m_paused = true;
}

void TimeCpt::resume() {
	m_substract_time += kiwi->getSysTick() - m_pause_time;
	m_paused = false;
}

uint32_t TimeCpt::get() {
	if (m_paused) {
		return m_pause_time - m_substract_time;;
	} else {
		return kiwi->getSysTick() - m_substract_time;
	}
}
