#ifndef Flight_H
#define Flight_H

#include <Godot.hpp>
#include <Area.hpp>
#include <CSGBox.hpp>
#include <AudioStreamPlayer.hpp>

namespace godot {

class Flight : public CSGBox {
    GODOT_CLASS(Flight, CSGBox)
private:
    bool touching;
    Node *player_in_area;
public:
    static void _register_methods();

    Flight();
    ~Flight();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _on_Area_area_entered(Area* a);
    void _on_Area_area_exited(Area* a);
    void _physics_process(float delta);
};
}
#endif
