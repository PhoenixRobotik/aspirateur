#pragma once

// C++17 : use variants

class Event
{
public:
    enum class Type { Move, Sleep, ServoG, ServoD, XL320, }
        type;

    // Move
    Pilot::TargetType moveType;
    double moveValue;

    // Sleep
    uint32_t duration;

    // ServoG, ServoD
    uint32_t angle;

    // ServoNum
    enum class Xl320Mode { Speed, Angle, }
        xlMode;
    uint32_t xlValue;

    static Event Move(Pilot::TargetType type, double value) {
        Event event;
        event.type = Type::Move;
        event.moveType = type;
        event.moveValue = value;
        return event;
    }
    static Event Sleep(int32_t duration) {
        Event event;
        event.type = Type::Sleep;
        event.duration = duration;
        return event;
    }
    static Event ServoG(uint32_t angle) {
        Event event;
        event.type = Type::ServoG;
        event.angle = angle;
        return event;
    }
    static Event ServoD(uint32_t angle) {
        Event event;
        event.type = Type::ServoD;
        event.angle = angle;
        return event;
    }
    static Event XL320(Xl320Mode mode, uint32_t value) {
        Event event;
        event.type = Type::XL320;
        event.xlValue = value;
        return event;
    }

    // Gets passed references
    // Returns "finished", as "does not need to be called again"
    bool execute(BoardKiwi& kiwi, Pilot& pilot, bool event_is_new) {
        bool finished = true;
        switch(type) {
        case Type::Move:
            finished = pilot.reach(moveType,  moveValue, event_is_new);
            // kiwi.sleep_ms(500);
            return finished;

        case Type::Sleep:
            kiwi.sleep_ms(duration);
            return finished;

        case Type::ServoG:

            return finished;

        case Type::ServoD:

            return finished;

        case Type::XL320:

            return finished;
        }
        return finished;
    }

};
