#ifndef SPAWN_POINT_H
#define SPAWN_POINT_H

#include <Godot.hpp>
#include <CSGBox.hpp>
#include <Area.hpp>
#include "StunAI.h"
#include <PackedScene.hpp>

namespace godot {

class SpawnPoint : public Spatial {
    GODOT_CLASS(SpawnPoint, Spatial)

private:
    Ref<PackedScene> ai_scene;
    bool ai_spawned;

public:
    static void _register_methods();

    SpawnPoint();
    ~SpawnPoint();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _on_area_entered(Area *otherArea);
    void _on_area_exited(Area *otherArea);
};
}
#endif
