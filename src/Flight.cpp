#include "Flight.h"
#include <stdlib.h>
#include <stdio.h>
#include <Input.hpp>
using namespace godot;

void Flight::_register_methods() {
    register_method("_process", &Flight::_process);
    register_method("_ready", &Flight::_ready);
    register_method("_on_Area_area_entered", &Flight::_on_Area_area_entered);
    register_method("_on_Area_area_exited", &Flight::_on_Area_area_exited);
    register_method("_physics_process",&Flight::_physics_process);
}

Flight::Flight() {
}

Flight::~Flight() {
    // add your cleanup here
}

void Flight::_on_Area_area_entered(Area* a){
    touching =true;
    player_in_area = a->get_parent();
}

void Flight::_on_Area_area_exited(Area* a){
    touching =false;
}

void Flight::_init() {
    touching = false;
}
void Flight::_ready() {
  get_node("Area")->connect("area_entered", this, "_on_Area_area_entered");
  get_node("Area")->connect("area_exited", this, "_on_Area_area_exited");
}
void Flight::_process(float delta) {
}
void Flight::_physics_process(float delta){
    Input *event = Input::get_singleton();

    //pickup flight powerup if R is pressed
    if(event->is_action_pressed("pickup_item") && touching && player_in_area != NULL){
        bool fly = player_in_area->get("flying");
        player_in_area->set("flying",!fly);
        if(!fly)
            player_in_area->set("gravity",Vector3(0,0,0));
        else
            player_in_area->set("gravity",Vector3(0,-9.8,0));
        Vector3 rotate = player_in_area->get("rotation");
        player_in_area->set("rotation",Vector3(0,rotate.y,rotate.z));
        get_parent()->remove_child(this);
    }
}
