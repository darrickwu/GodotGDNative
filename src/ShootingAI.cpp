#include "ShootingAI.h"
#include <stdlib.h>
#include <stdio.h>
#include <Input.hpp>
#include <SceneTree.hpp>
#include <Ref.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
using namespace godot;
int fireBullet = 10;
void ShootingAI::_register_methods() {
    register_method("_process", &ShootingAI::_process);
    register_method("_ready", &ShootingAI::_ready);
    register_method("_physics_process",&ShootingAI::_physics_process);
    register_method("_on_Area_area_entered", 
        &ShootingAI::_on_Area_area_entered);
    register_property<ShootingAI, int>("speed", &ShootingAI::speed,4);

}

ShootingAI::ShootingAI() {
}

ShootingAI::~ShootingAI() {
    // add your cleanup here
}

void ShootingAI::_init() {
    playerPos = Vector3(0,0,0);
    speed = 4;
    direction = Vector3(0,0,1);
}

void ShootingAI::_ready() {
    wayPtCur = cast_to<Spatial>(get_node("../waypointv2"))
        ->get_translation();
    
    look_at(wayPtCur, Vector3(0,1,0));
    ray1 = (RayCast*)get_node("RayCastt");
    laser = (Spatial*)get_node("RayCastt/CSGBox");
    laser->set_visible(false);
    ray1->set_enabled(true);
    turret = (Spatial*)get_node("Spatial");
    get_node("Area")->connect("area_entered",
     this, "_on_Area_area_entered");

}

void ShootingAI::_process(float delta) {
}

void ShootingAI::shootOnce(Vector3 dir){
    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    Ref<PackedScene> BulletScene = resourceLoader->load("res://Bullet.tscn");
    godot::Bullet* bull = static_cast<godot::Bullet*>(BulletScene->instance());
    bull->set("translation",get_translation());
    bull->set("direction",dir);
    get_node("/root/Game")->add_child(bull);
    Bullets.push_back(bull);
    //add it to a group for detection
    //Create an instance of a bullet
    //add bullet to our vector of current bullets
}

//could potentially have an array of waypoints
//raycasting WILL CRASH THE GAME at certain angles.
void ShootingAI::_physics_process(float delta){
    
    //need to find better way to find player node, than in physx process
    playerPos = cast_to<Spatial>(get_node("/root/Game/localPlayer"))
        ->get_translation();
    
    //playerPos = get_node("root/Game/localPlayer")->get("translation");
    
    //if we can see the player
    //a to b
    // source to playerpos
    Vector3 source = this->get_translation();
    ray1->set_cast_to(((Vector3)(playerPos - source)));
     turret->look_at(playerPos, Vector3(0,1,0));
    ray1->set_rotation(turret->get_rotation());
    rayTgt = cast_to<Node>(ray1->get_collider());

    //player detected in line of sight
    
    if(ray1->is_colliding() && rayTgt->get_name() == "localPlayer"){
        laser->set_visible(true);
        //start shooting
        if(fireBullet >= 60){
            cast_to<AudioStreamPlayer>
                (get_node("./shootSound"))->play();
            shootOnce(((Vector3)(playerPos - source)).normalized());
           fireBullet = 0;
        }
        fireBullet++;
    }
    else{
        //move to wayptcur if cant see player
        laser->set_visible(false);
        look_at(wayPtCur, Vector3(0,1,0));
        direction = wayPtCur - source;
        direction.normalize();
        Vector3 new_pos = source + (direction * speed * delta);
        this->set_translation(new_pos);
    }
    

    //delete bullets
    for(int i =0;i<Bullets.size();i++)
    {
        if((int)Bullets[i]->get("timeAlive") > 100)
        {
            get_node("/root/Game")->remove_child(Bullets[i]);
            Bullets.erase(Bullets.begin() + i);
        }
    }
    //**********************
    /*
        Basic AI Functionality
        1. Check if character is near AI, and it can see the player(RayCast?)
            1. patrolling
            2. shooting
            3. dying if player touches it
        2. Check all current bullets and kill any that have lasted too long
        
    */
    //*******************
    
    /*
        Wandering:
            -AI walks to certain way points in a predictable pattern
            Example:
            ------------------------------------
            |            (A)                    |
            |           /   \                   |
            |          /     \                  |
            |         AI      \                 |
            |                 (B)               |
            -------------------------------------
            AI walks to point A, then to point B
     */
    /*
        Shooting:
            If the character is within a certain distance from the AI and visable, we start shooting at the character. Calling shootOnce() to add a bullet to the current bullets in the system.
        Checking visability:
            We can make a ray cast from the AI to the player and see if it interacts with anything, if it can't see the player, continue moving on current path
     
     */
    /*
        Handling bullets in the system:
            The bullets will be handled like particles, they only live for X-amount of seconds/frames, then disappear
            We have a vector that keeps track of the current bullets in the system and we check each bullet to see if it needs to be deleted.
            Something like:
                for(int i = 0; i < bullets.size(); i++)
                {
                    if(bullets[0].timeAlive > 5)
                        bullets.erase(bullets.begin()+i);
                }
     
     */
}

void ShootingAI::_on_Area_area_entered(Area* a){
    String name = a->get_parent()->get_name();
    Godot::print("am collidingwith area" + name);
    //die if you touch the player
    if(name == "localPlayer"){
        get_parent()->remove_child(this);
    }
    //switch waypoints and patrol
    //ideally it would have an array of waypts, and collide with their group
    if(name == "wayPtOne"){
        wayPtCur = cast_to<Spatial>(get_node("../waypointv2"))
        ->get_translation();
        //direction = Vector3(0,0,1);

    } else if(name == "wayPtTwo"){
        wayPtCur = cast_to<Spatial>(get_node("../waypoint"))
        ->get_translation();
       // direction = Vector3(0,0,-1);

    }
}
