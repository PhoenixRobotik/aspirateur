#pragma once

#include <stdint.h>

class TimeCpt {
public:
    TimeCpt() {
        init();
    }
    ~TimeCpt() { }

    void init () {reset();}
    void reset();
    void pause();
    void resume();
    uint32_t get_us();

private:
    uint32_t m_substract_time;
    uint32_t m_pause_time;
    bool m_paused;
};
