#include "Bullet.h"
#include <stdlib.h>
#include <stdio.h>
#include <Input.hpp>
using namespace godot;

void Bullet::_register_methods() {
    register_method("_process", &Bullet::_process);
    register_method("_ready", &Bullet::_ready);
    register_method("_on_Area_area_entered", &Bullet::_on_Area_area_entered);
    register_method("_physics_process",&Bullet::_physics_process);
    register_property<Bullet, int>("speed", &Bullet::speed,4);
    register_property<Bullet, int>("timeAlive", &Bullet::timeAlive,0);
    register_property<Bullet, Vector3>("direction", &Bullet::direction,Vector3(0,0,1));
    
}

Bullet::Bullet() {
}

Bullet::~Bullet() {
    // add your cleanup here
}

void Bullet::_on_Area_area_entered(Area* a){
    
}

void Bullet::_init() {
    speed = 20;
    timeAlive = 0;
    direction = Vector3(0,0,1);
}
void Bullet::_ready() {
  get_node("Area")->connect("area_entered", this, "_on_Area_area_entered");
}
void Bullet::_process(float delta) {
}
void Bullet::_physics_process(float delta){
    set_translation(get_translation()+direction*speed*delta);
    timeAlive++;
}
