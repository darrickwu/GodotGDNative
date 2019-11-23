#ifndef StunAI_H
#define StunAI_H

#include <Godot.hpp>
#include <Area.hpp>
#include <CSGBox.hpp>
#include "Player.h"

#define MAX_DISTANCE 7

namespace godot {

class StunAI : public CSGBox {
    GODOT_CLASS(StunAI, CSGBox)
private:
    bool spawned;
    Vector3 center;
    Vector3 direction;
    Vector3 goal;
    float speed;
    Player *player;

public:
    static void _register_methods();

    StunAI();
    ~StunAI();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _physics_process(float delta);
    void _spawnAI(Vector3 center, Node *p);
    void _despawnAI();
    void _on_stunned();
};
}
#endif
