#pragma once

#include "fake_remote.h"

//m.s-1
static const double DIST_MAX_SPEED   (0.209);
//m.s-2 (unused)
static const int DIST_ACC            (1000);
//m.s-2 (unused)
static const int DIST_DEC            (1000);
//deg.s-1
static const int ANGL_MAX_SPEED      (92);
//deg.s-2 (unused)
static const int ANGL_ACC            (1000);
//deg.s-2 (unused)
static const int ANGL_DEC            (1000);
// time offset due to trame sending
static const int UNIT_TIME_us (DEAD_TIME + TRAME_TIME);



class Pilot {
public:
    Pilot(std::shared_ptr<FakeRemote> _remote)
    : remote (_remote)
    {
        init();
    }
    ~Pilot() { }

    enum Direction {
        right     = FakeRemote::Trame::droite,
        left      = FakeRemote::Trame::gauche,
        frontward = FakeRemote::Trame::avant,
        backward  = FakeRemote::Trame::arriere,
    };

    enum class TargetType {
        angle,
        distance,
    };

    void init() {}
    void reach(TargetType target_type, float value);

private:
    std::shared_ptr<FakeRemote> remote;

    void go(Direction direction, float time_us);

    Direction current;
    float current_time_us_elapsed;
    float current_time_us_elapsed;
};
