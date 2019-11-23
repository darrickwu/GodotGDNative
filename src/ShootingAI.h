#ifndef ShootingAI_H
#define ShootingAI_H

#include <Godot.hpp>
#include <Area.hpp>
#include <CSGBox.hpp>
#include <CSGSphere.hpp>
#include <vector>
#include <RayCast.hpp>
#include "Bullet.h"
#include <AudioStreamPlayer.hpp>

namespace godot {

class ShootingAI : public CSGBox {
    GODOT_CLASS(ShootingAI, CSGBox)
private:
    // a vector of bullets
    //std::vector<CSGSphere *> Bullets;
    Vector3 position;
    Vector3 direction;
    int speed;
    RayCast* Visible;
    Vector3 wayPtCur;
    Vector3 playerPos;
    RayCast* ray1;
    Node* rayTgt;
    std::vector<godot::Bullet *> Bullets;
    Spatial* turret;
    Spatial* laser;
public:
    static void _register_methods();

    ShootingAI();
    ~ShootingAI();
    
    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _physics_process(float delta);
    void shootOnce(Vector3 dir);
    void _on_Area_area_entered(Area* a);
};
}
#endif
