#ifndef STAMINABAR_H
#define STAMINABAR_H

#include <Godot.hpp>
#include <ColorRect.hpp>

namespace godot {

class StaminaBar : public ColorRect {
    GODOT_CLASS(StaminaBar, ColorRect)

private:
    float current_size;

public:
    static void _register_methods();

    StaminaBar();
    ~StaminaBar();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _on_stamina_changed(float new_stamina);
    void connect_stamina_signal(Node *player);
};
}
#endif

