#include "funny_action.h"
#include "board_kiwi.h"


// pass pwm to the class ?

void FunnyAction::init()
{
    go_idle();
}

void FunnyAction::go_idle()
{
    kiwi->ServoFunnyAction.setMicrosec(IDLE_POSITION);
}

void FunnyAction::launch()
{
    kiwi->ServoFunnyAction.setMicrosec(TRIG_POSITION);
    kiwi->sleep_ms(300);
    go_idle();
}
