#include "CameraRay.h"
#include <stdlib.h>
#include <stdio.h>
#include <Input.hpp>
using namespace godot;

void CameraRay::_register_methods() {
    register_method("_process", &CameraRay::_process);
    register_method("_ready", &CameraRay::_ready);
    register_method("_physics_process",&CameraRay::_physics_process);
}

CameraRay::CameraRay() {
}

CameraRay::~CameraRay() {
    // add your cleanup here
}
void CameraRay::_physics_process(float delta){
    if(ray->is_colliding())
    {
        Object* o = ray->get_collider();
        //reveal old object, hide new object
        if(o != obj && obj != NULL)
            obj->set("visible",true);
        //hide object if in way of camera
        obj = o;
        o->set("visible",false);
    }
    else
    {
        //if obj is currently hidden reveal it if not in way
        if(obj != NULL)
        {
            obj->set("visible",true);
            obj = NULL;
        }
    }
    
}

void CameraRay::_init() {
}
void CameraRay::_ready() {
    ray = (RayCast*)get_node("RayCast");
    ray->set_cast_to(Vector3(0,-.3,-1.4));
    ray->set_enabled(true);
    obj=NULL;
}
void CameraRay::_process(float delta) {
}
