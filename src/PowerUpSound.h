
#ifndef POWERSOUND_H
#define POWERSOUND_H

#include <Godot.hpp>
#include <AudioStreamPlayer.hpp>

namespace godot {

class PowerUpSound : public Node {
    GODOT_CLASS(PowerUpSound, Node)

private:
public:
    static void _register_methods();

    PowerUpSound();
    ~PowerUpSound();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _on_stamina_obtained();
};
}
#endif
