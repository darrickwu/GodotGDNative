#include "PowerUpSound.h"

using namespace godot;

void PowerUpSound::_register_methods() {
    register_method("_ready", &PowerUpSound::_ready);
    register_method("_on_stamina_obtained",&PowerUpSound::_on_stamina_obtained);
}

PowerUpSound::PowerUpSound() {
}

PowerUpSound::~PowerUpSound() {
}

void PowerUpSound::_init() {
}

void PowerUpSound::_ready() {
    get_node(NodePath("../KinematicBody"))->connect("stamina_obtained", this, "_on_stamina_obtained");
}

void PowerUpSound::_on_stamina_obtained() {
    cast_to<AudioStreamPlayer>(get_node("./StaminaSound"))->play();
}