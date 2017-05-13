#pragma once

#include "fake_remote.h"

//m.s-1
#define DIST_MAX_SPEED      (0.209)
//m.s-2 (unused)
#define DIST_ACC            (1000)
//m.s-2 (unused)
#define DIST_DEC            (1000)
//deg.s-1
#define ANGL_MAX_SPEED      (92)
//deg.s-2 (unused)
#define ANGL_ACC            (1000)
//deg.s-2 (unused)
#define ANGL_DEC            (1000)
// time offset due to trame sending
#define UNIT_TIME_us (DEAD_TIME + TRAME_TIME)



class Pilot {
public:
    Pilot(std::shared_ptr<FakeRemote> _remote)
    : remote (_remote)
    {
        init();
    }
    ~Pilot() { }

    typedef enum Direction {
        right     = FakeRemote::Trame::droite,
        left      = FakeRemote::Trame::gauche,
        frontward = FakeRemote::Trame::avant,
        backward  = FakeRemote::Trame::arriere,
    } direction_t;

    typedef enum TargetType {
        angle,
        distance,
    } target_type_t;

    void init() {}
    void reach(target_type_t target_type, float value);

private:
    std::shared_ptr<FakeRemote> remote;

    void go(direction_t direction, float time_us);
};
