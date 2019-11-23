#include "SpawnPoint.h"
#include <stdlib.h>
#include <stdio.h>
#include <ResourceLoader.hpp>

using namespace godot;
using namespace std;

void SpawnPoint::_register_methods() {
    register_method("_process", &SpawnPoint::_process);
    register_method("_ready", &SpawnPoint::_ready);
    register_method("_on_area_entered", &SpawnPoint::_on_area_entered);
    register_method("_on_area_exited", &SpawnPoint::_on_area_exited);
}

SpawnPoint::SpawnPoint() {
}

SpawnPoint::~SpawnPoint() {
}

void SpawnPoint::_init() {
}

void SpawnPoint::_ready() {
    get_node("./Area")->connect("area_entered", this, "_on_area_entered");
    get_node("./Area")->connect("area_exited", this, "_on_area_exited");
    ai_spawned = false;
}

void SpawnPoint::_process(float delta) {
}

void SpawnPoint::_on_area_entered(Area *otherArea) {
    cout << "in area entered" << endl;
    if(!ai_spawned) {
        cout << "spawning ai in spawnpoint" << endl;
        ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
        ai_scene = resourceLoader->load("res://Stun AI.tscn");
        StunAI *ai = cast_to<StunAI>(ai_scene->instance());
        Vector3 spawn_pos = this->get_translation();
        Vector3 ai_pos = Vector3(spawn_pos.x, spawn_pos.y + 1, spawn_pos.z);
        ai->set_translation(ai_pos);
        ai->_spawnAI(spawn_pos, otherArea->get_parent());
        get_node("/root/Game")->add_child(ai);
        ai_spawned = true;
    }
}

void SpawnPoint::_on_area_exited(Area *otherArea) {
    cout << "in exit" << endl;
    if(ai_spawned) {
        StunAI *ai = cast_to<StunAI>(ai_scene->instance());
        ai->_despawnAI();
        ai_spawned = false;
    }
}

