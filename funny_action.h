#pragma once

#include "pwm.h"

static const int TRIG_POSITION (560);
static const int IDLE_POSITION (670);


class FunnyAction {
public:
    FunnyAction()
    {
        init();
    }
    ~FunnyAction() { }

    void init();
    void go_idle();
    void launch();

private:
};
