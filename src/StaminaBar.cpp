#include "StaminaBar.h"
#include <stdlib.h>
#include <stdio.h>
using namespace godot;
using namespace std;

#define MAX_SIZE 400
#define SCALE 4

void StaminaBar::_register_methods() {
    register_method("_process", &StaminaBar::_process);
    register_method("_ready", &StaminaBar::_ready);
    register_method("_on_stamina_changed", &StaminaBar::_on_stamina_changed);
}

StaminaBar::StaminaBar() {
}

StaminaBar::~StaminaBar() {
}

void StaminaBar::_init() {
    current_size = MAX_SIZE;
}

void StaminaBar::_ready() { 
  /////gt_node("")->connect("stamina_changed", this, "_on_stamina_changed");
}

void StaminaBar::_process(float delta) {
}

void StaminaBar::connect_stamina_signal(Node *player) {
    player->connect("stamina_changed", this, "_on_stamina_changed");
}

void StaminaBar::_on_stamina_changed(float new_stamina) {
    current_size = new_stamina * SCALE;
    if(current_size > MAX_SIZE)
        current_size = MAX_SIZE;
    Vector2 old_size = get_size();
    set_size(Vector2(current_size, old_size.y));
}
