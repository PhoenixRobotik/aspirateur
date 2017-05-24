#include "board_kiwi.h"
#include "pilot.h"

#include <cmath>
#include <stdint.h>



bool Pilot::reach(TargetType target_type, float value, bool target_is_new)
{
    if (target_is_new) {
        compute(target_type, value);
        m_time_server->reset();
    }
    return go();
}

void Pilot::compute(TargetType target_type, float value)
{
    float time_needed_us;
    switch(target_type) {
        case TargetType::angle:
            time_needed_us = std::abs(1000000.0*value/ANGL_MAX_SPEED);
            if (value < 0) {
                m_current_direction = right;
            } else if (value > 0) {
                m_current_direction = left;
            }
            break;
        case TargetType::distance:
            time_needed_us = std::abs(1000000.0*value/DIST_MAX_SPEED);
            if (value < 0) {
                m_current_direction = backward;
            } else if (value > 0) {
                m_current_direction = frontward;
            }
            break;
    }
    m_time_needed_us = static_cast<int32_t>(std::round(time_needed_us));
    if (m_time_needed_us < UNIT_TIME_us) {
        m_time_needed_us = UNIT_TIME_us;
    }
}

bool Pilot::go() {
    int32_t remaining_time = m_time_needed_us - m_time_server->get_us();
    if (remaining_time <= 0 ) {
        stop();
        return true;
    } else if (remaining_time < TRAME_TIME) {
        kiwi->sleep_us(remaining_time);
        stop();
        return true;
    } else {
        remote->send_trame((FakeRemote::Trame) m_current_direction);
        return false;
    }
}

void Pilot::stop() {
    remote->send_trame(FakeRemote::Trame::pause);
}
