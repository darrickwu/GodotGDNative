#ifndef CameraRay_H
#define CameraRay_H

#include <Godot.hpp>
#include <RayCast.hpp>
#include <Camera.hpp>

namespace godot {

class CameraRay : public Camera {
    GODOT_CLASS(CameraRay, Camera)

private:
    RayCast* ray;
    Object* obj;
public:
    static void _register_methods();

    CameraRay();
    ~CameraRay();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _physics_process(float delta);
};
}
#endif
