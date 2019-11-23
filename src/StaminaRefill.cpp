#include "StaminaRefill.h"
#include <stdlib.h>
#include <stdio.h>
#include <Input.hpp>
using namespace godot;

void StaminaRefill::_register_methods() {
    register_method("_process", &StaminaRefill::_process);
    register_method("_ready", &StaminaRefill::_ready);
    register_method("_on_Area_area_entered", &StaminaRefill::_on_Area_area_entered);
}

StaminaRefill::StaminaRefill() {
}

StaminaRefill::~StaminaRefill() {
    // add your cleanup here
}

void StaminaRefill::_on_Area_area_entered(Area* a){
  Node *player = a->get_parent(); 
  int oldStamina = player->get("stamina");
  player->set("stamina",oldStamina+50);
  get_parent()->remove_child(this);
}

void StaminaRefill::_init() {
}
void StaminaRefill::_ready() { 
  get_node("Area")->connect("area_entered", this, "_on_Area_area_entered");
}
void StaminaRefill::_process(float delta) {
}
