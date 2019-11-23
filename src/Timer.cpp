#include "Timer.h"
#include <stdlib.h>

using namespace godot;
using namespace std;

void Timer::_register_methods() {
    register_method("_process", &Timer::_process);
    register_method("_ready", &Timer::_ready);
    register_method("_on_use_timer", &Timer::_on_use_timer);
    register_property<Timer, double>("total_time", &Timer::total_time, DEFAULT_TOTAL);
    register_property<Timer, double>("time_passed", &Timer::time_passed, 0.0);
    register_property<Timer, bool>("in_use", &Timer::in_use, false);
    register_signal<Timer>("timer_up");
}

Timer::Timer() {
}

Timer::~Timer() {
}

void Timer::_init() {
    total_time = DEFAULT_TOTAL;
    time_passed = 0.0;
    in_use = false;
}

void Timer::_ready() {
    set_percent_visible(1.0);
    set_text("TIMER BOI");
}

void Timer::connect_timer_signal(Node *player) {
    player->connect("use_timer", this, "_on_use_timer");
}

void Timer::_process(float delta) {
    if(in_use) {
        time_passed += delta;
        if(total_time - time_passed <= 0.0) {
            time_passed = 0.0;
            emit_signal("timer_up");
            in_use = false;
            set_percent_visible(0.0);
        }
        else {
            set_text(String::num(total_time - time_passed, 2));
        }
    }
}

void Timer::_on_use_timer() {
    if(!in_use) {
        set_percent_visible(1.0);
        in_use = true;
    }
}