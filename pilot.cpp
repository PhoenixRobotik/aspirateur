#include "board_kiwi.h"
#include "pilot.h"

#include <cmath>
#include <stdint.h>


void Pilot::reach(TargetType target_type, float value)
{
    float time_us;
    switch(target_type) {
        case TargetType::angle:
            time_us = std::abs(1000000.0*value/ANGL_MAX_SPEED);
            if (value < 0) {
                go(right, time_us);
            } else if (value > 0) {
                go(left, time_us);
            }
            break;
        case TargetType::distance:
            time_us = std::abs(1000000.0*value/DIST_MAX_SPEED);
            if (value < 0) {
                go(backward, time_us);
            } else if (value > 0) {
                go(frontward, time_us);
            }
            break;
    }
}

void Pilot::go(Direction direction, float time_us) {
    
    if (time_us < UNIT_TIME_us) {
        time_us = UNIT_TIME_us;
    }
    
    uint32_t trame_cpt  = static_cast<uint32_t>(std::round(time_us/UNIT_TIME_us));
    uint32_t crumb_time = static_cast<uint32_t>(std::round(time_us) - trame_cpt * UNIT_TIME_us);
    
    for (uint32_t i = 0; i < trame_cpt; i++) {
        remote->send_trame((FakeRemote::Trame) direction);
    }

    kiwi->sleep_us(crumb_time);
    stop();
}

void Pilot::stop() {
    remote->send_trame(FakeRemote::Trame::pause);
}
