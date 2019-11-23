#ifndef TIMER_H
#define TIMER_H

#include <Godot.hpp>
#include <RichTextLabel.hpp>
#define DEFAULT_TOTAL 3.0

namespace godot {

class Timer : public RichTextLabel {
    GODOT_CLASS(Timer, RichTextLabel)

private:
    
    double time_passed;
    double total_time;
    bool in_use;

public:
    static void _register_methods();

    Timer();
    ~Timer();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _on_use_timer();
    void connect_timer_signal(Node *player);
};
}
#endif
