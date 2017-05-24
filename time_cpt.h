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
    int32_t get_us();

private:
    int32_t m_substract_time;
    int32_t m_pause_time;
    bool m_paused;
};
