#ifndef StaminaRefill_H
#define StaminaRefill_H

#include <Godot.hpp>
#include <Area.hpp>
#include <CSGBox.hpp>
#include <AudioStreamPlayer.hpp>

namespace godot {

class StaminaRefill : public CSGBox {
    GODOT_CLASS(StaminaRefill, CSGBox)

public:
    static void _register_methods();

    StaminaRefill();
    ~StaminaRefill();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _on_Area_area_entered(Area* a);
};
}
#endif
