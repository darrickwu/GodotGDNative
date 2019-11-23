#include "StunAI.h"
#include <stdlib.h>
#include <stdio.h>
#include <Input.hpp>
using namespace godot;

using namespace std;

void StunAI::_register_methods() {
    register_method("_process", &StunAI::_process);
    register_method("_ready", &StunAI::_ready);
    register_method("_on_stunned", &StunAI::_on_stunned);
    register_method("_physics_process",&StunAI::_physics_process);
    register_signal<StunAI>("despawn_ai");
}

StunAI::StunAI() {
}

StunAI::~StunAI() {
    // add your cleanup here
}

void StunAI::_init() {
}

void StunAI::_ready() {
    speed = 2;
}

void StunAI::_process(float delta) {
}

void StunAI::_spawnAI(Vector3 spawn_center, Node *p){
    spawned = true;
    center = spawn_center;
    player = cast_to<Player>(p);
    goal = player->get_translation();
    player->connect("stunned", this, "_on_stunned");
}

void StunAI::_despawnAI() {
    spawned = false;
    player = nullptr;
    goal = center;
    queue_free();
}

void StunAI::_on_stunned() {
    _despawnAI();
}

void StunAI::_physics_process(float delta){
    if(spawned) {
        Vector3 curr_pos = this->get_translation();
        if((curr_pos - center).length() <= 10) {
            direction = goal - curr_pos;
            goal = player->get_translation();
            Vector3 new_pos = curr_pos + (direction * speed * delta);
            this->set_translation(new_pos);
        }
    }
    //**********************
       /*
           Basic AI Functionality
           1. Check if character is near AI
               1a. If it is, spawn and start chasing character.
               1b. If it isnt, don't spawn
           
       */
       //*******************
       
       /*
            Spawning:
                We have certain spawn points throughout the map, if the player gets within a certain distance of the a spawn point we spawn a stun AI from that point
        */
       /*
            Chasing Player:
                When we are chasing the player we will need to make it look natural somehow, smoothing the path to the player
        
        */
       /*
            Stuning:
                We can use area_entered signal to tell if we have intersected the player.
                The player then gets stuned for a few seconds and the Stun AI disappears
        */
        /*
            Despawning AI???
                Either after a certain amount of time, or distance from spawn point
         */
}
