#ifndef Player_H
#define Player_H

#include <Godot.hpp>
#include <InputEvent.hpp>
#include <KinematicBody.hpp>
#include <RayCast.hpp>
#include <AudioStreamPlayer.hpp>
#include <Area.hpp>

namespace godot {

class Player : public KinematicBody {
    GODOT_CLASS(Player, KinematicBody)

private:
    Vector3 gravity;
    Vector3 direction;
    Vector3 velocity;
    Vector3 slavePosition;
    int64_t slaveMovement;
    int doubleJump; 
    bool flying;
    RayCast* ray1;
    RayCast* ray2;
    bool onLedge;
    bool hanging;
    bool hangAnimInProgress;
    bool pullUpInProgress;
    bool should_play_fail;
    bool stunned;
    
    
public:
    static void _register_methods();
    float stamina;
    Player();
    ~Player();

    void _init(); // our initializer called by Godot
    void _moveCharacter(float delta, int movement);
    void _ready(); 
    void _input(InputEvent *event);
    void _process(float delta);
    void _physics_process(float delta);
    void _on_timer_up();
    void _on_area_entered(Area *area);
    void _on_area_exited(Area *area);
    void _on_Area_area_entered(Area* a);
    void init(String nickname, Vector3 startPosition, bool isSlave);
};
}
#endif
