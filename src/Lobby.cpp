#include "Lobby.h"
#include <stdlib.h>
#include <stdio.h>
#include <SceneTree.hpp>
#include <Label.hpp>

using namespace godot;

void Lobby::_register_methods() {
    register_method("_ready", &Lobby::_ready);
    register_method("_on_start_pressed", &Lobby::_on_start_pressed);
}

Lobby::Lobby() {
}

Lobby::~Lobby() {
}

void Lobby::_init() {
}

void Lobby::_ready() {
    get_node("./StartButton")->connect("pressed", this, "_on_start_pressed");
}

void Lobby::_on_start_pressed() {
    this->get_tree()->change_scene("res://main.tscn");
}
