#ifndef Bullet_H
#define Bullet_H

#include <Godot.hpp>
#include <Area.hpp>
#include <CSGSphere.hpp>

namespace godot {

class Bullet : public CSGSphere {
    GODOT_CLASS(Bullet, CSGSphere)
private:
    Vector3 direction;
    int speed;
    int timeAlive;
public:
    static void _register_methods();

    Bullet();
    ~Bullet();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _on_Area_area_entered(Area* a);
    void _physics_process(float delta);
};
}
#endif
