#include "Player.h"
#include <stdlib.h>
#include <stdio.h>
#include <Input.hpp>
#include <SceneTree.hpp>

using namespace godot;

void Player::_register_methods() {
    register_method("_process", &Player::_process);
    register_method("_on_Area_area_entered", &Player::_on_Area_area_entered);
    register_method("_ready", &Player::_ready,GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_physics_process",
      &Player::_physics_process,GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_input",&Player::_input);
    register_method("_moveCharacter", 
      &Player::_moveCharacter, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_on_timer_up", &Player::_on_timer_up);
    register_method("_on_area_entered", &Player::_on_area_entered);
    register_method("_on_area_exited", &Player::_on_area_exited);
    register_property<Player, Vector3>("gravity", 
      &Player::gravity,Vector3(0,0,0));
    register_property<Player, Vector3>("slavePosition", 
      &Player::slavePosition,Vector3(0,0,0),GODOT_METHOD_RPC_MODE_PUPPET);
    register_property<Player, Vector3>("direction", 
      &Player::direction,Vector3(0,0,0),GODOT_METHOD_RPC_MODE_PUPPET);
    register_property<Player, Vector3>("velocity",  
      &Player::velocity,Vector3(0,0,0));
    register_property<Player, int>("doubleJump", 
      &Player::doubleJump,0);
    register_property<Player, float>("stamina", &Player::stamina,100);
    register_property<Player, bool>("flying", &Player::flying,false);
    register_signal<Player>("stamina_changed", 
      "new_stamina", GODOT_VARIANT_TYPE_INT);
    register_signal<Player>("use_timer");
    register_signal<Player>("stunned");
    register_property<Player, int64_t>("slaveMovement", 
      &Player::slaveMovement, static_cast<int64_t>(0), 
      GODOT_METHOD_RPC_MODE_PUPPET);
    register_method("init", &Player::init, GODOT_METHOD_RPC_MODE_DISABLED);
}

Player::Player() {
}

Player::~Player() {
    // add your cleanup here
}

void Player::_init() {
  gravity = Vector3(0,-9.8,0);
  direction = Vector3(1,0,0);
  velocity = Vector3(0,0,0);
  doubleJump = 0;
 
  stamina = 100;
  flying = false;
  onLedge = false;
  hanging = false;
  stunned = false;
  should_play_fail = true;
}
void Player::_ready() { 
  ray1 = (RayCast*)get_node("RayCast");
  ray2 = (RayCast*)get_node("RayCast2");
  set_translation(Vector3(-39,7.5,-4.5));
  slavePosition = get_translation();
  ray1->set_enabled(true);
  ray2->set_enabled(true);
  ray1->set_cast_to(Vector3(0,-1,0));
  ray2->set_cast_to(Vector3(0,-1,0));
  get_node("../Timer")->connect("timer_up", this, "_on_timer_up");
  get_node("./Area")->connect("area_entered", this, "_on_area_entered");
  get_node("./Area")->connect("area_exited", this, "_on_area_exited");
  get_node("Area")->connect("area_entered", this, "_on_Area_area_entered");
  cast_to<AudioStreamPlayer>(get_node("../BackgroundMusic"))->play();
}
void Player::_on_Area_area_entered(Area* a){
    String name = a->get_parent()->get_name();
    //Godot::print(name);
    //should check if in group
    if(name == "Bullet")
        set_translation(Vector3(-40,12,-4.5));
    if(name == "finnish"){
      this->get_tree()->change_scene("res://gameEnd.tscn");
    }
}
void Player::_physics_process(float delta){
   //set_translation(get_translation()+delta*velocity);
  //disable gravity if touching floor
  /*AudioStreamPlayer *flight_player = 
  //cast_to<AudioStreamPlayer>(get_node("./FlyingPlayer"));
  velocity += delta * gravity;
  //check for ledges
  if (flying){
    //emit_signal("use_timer");
    translate(Vector3(0,0,-.3));
    if(!flight_player->is_playing())
      flight_player->play();
  }
  else {
    if(flight_player->is_playing())
      flight_player->stop();
  }

  Input *event = Input::get_singleton();
  if(event->is_action_pressed("pickup_item")) {
    String sound = should_play_fail ? "./FailSound" : "./FlightPickupSound";
    const char *sound2 = should_play_fail ? "./FailSound" : "./FlightPickupSound";
    std::cout << "in physics " << should_play_fail  << " " << sound2 << 
    std::endl;
    AudioStreamPlayer *player = cast_to<AudioStreamPlayer>(get_node((NodePath)sound));
    if(!player->is_playing())
      player->play();
    if(!should_play_fail && !player->is_playing())
      should_play_fail = true;
  }
  //forward
  if(event->is_action_pressed("ui_up")){
    //pitch up if flying
    if (flying){
      set_rotation(get_rotation()+Vector3(1*M_PI/180.0,0,0));
    }
    //if grounded, or jumping player can move
    //can jump off ledges
    else if(ray1->is_colliding() || doubleJump >= 1){
      set_translation(get_translation()+direction*.1);
      if(stamina > 0)
        stamina -= .5;
      emit_signal("stamina_changed", stamina);
    }
    //on ledge if front ray isnt colliding and not jumping
    else if ((!ray1->is_colliding()) && doubleJump ==0){
      onLedge = true;
    } else {
      onLedge = false;
    }
  }
  //back
  if(event->is_action_pressed("ui_down")){
    if (flying){
      set_rotation(get_rotation()+Vector3(-1*M_PI/180.0,0,0));
    }else {
      if(ray2->is_colliding() || doubleJump >= 1)
        set_translation(get_translation()-direction*.1);
      if(stamina > 0)
        stamina -= .5;
      emit_signal("stamina_changed", stamina);
    }
  }
  //rotations
  if(event->is_action_pressed("ui_right"))
  {
    // set_rotation(get_rotation()+Vector3(0,-5*M_PI/180.0,0));
    Vector2 newDir = Vector2(direction.x,direction.z).rotated(.05);
    direction = Vector3(newDir.x,0,newDir.y).normalized();
    rotate(Vector3(0,-1,0), .05);
  }
  if(event->is_action_pressed("ui_left"))
  {
    // set_rotation(get_rotation()+Vector3(0,5*M_PI/180.0,0));
    Vector2 newDir = Vector2(direction.x,direction.z).rotated(-.05);
    direction = Vector3(newDir.x,0,newDir.y).normalized();
    rotate(Vector3(0,1,0), .05);
  }
  //strafing, q,e
  //will not stop at ledges
  if(event->is_action_pressed("strafe_right"))
  {
    translate(Vector3(.25,0,0));
    if(stamina > 0)
        stamina -= .4;
    emit_signal("stamina_changed", stamina);
  }
  if(event->is_action_pressed("strafe_left"))
  {
    translate(Vector3(-.25,0,0));
    if(stamina > 0)
        stamina -= .5;
    emit_signal("stamina_changed", stamina);
  }


  //flying, using wasd
  //default f
  if(event->is_action_just_pressed("toggle_fly"))
  { 
    if (flying){
      //disable flight
      flying = false;
      gravity.y = -9.8;
      set_rotation(Vector3(0,get_rotation().y,get_rotation().z));
    } else {
      flying = true;
      velocity.y = 0;
      gravity.y = 0;
    }
  }

  //hang on ledge, or fall if already hanging
  //default ctrl
  if(event->is_action_just_pressed("fall_ledge")){
    if(hanging){
      hanging = false;
      gravity = Vector3(0,-9.8,0);
    } else if (!hanging && onLedge){
      hanging=true;
      onLedge = false;
      hangAnimInProgress = true;
      gravity = Vector3(0,0,0);
    }
  }

  //move until back ray is no longer colliding, and flip 180 to face ledge
  if(hangAnimInProgress){
    set_translation(get_translation()+direction*.1);
    
    if (!ray2->is_colliding()){
      translate(Vector3(-2,-2,0));
      Vector2 newDir = Vector2(direction.x,direction.z).rotated(M_PI);
      direction = Vector3(newDir.x,0,newDir.y).normalized();
      rotate(Vector3(0,-1,0), M_PI);
      hangAnimInProgress = false;
    }
  }

  //move until back ray is colliding, and pull up
  if(pullUpInProgress){
    set_translation(get_translation()+direction*.1);
    
    if (ray2->is_colliding()){
      gravity = Vector3(0,-9.8,0);
      pullUpInProgress = false;
    }
  }

  velocity = move_and_slide(velocity,Vector3(0,-1,0));
  //reset jumps once landing
  if(doubleJump > 0 && velocity.y == 0.0)
    doubleJump = 0;*/
    
    if(is_network_master())
    {
        AudioStreamPlayer *flight_player = 
          cast_to<AudioStreamPlayer>(get_node("./FlyingPlayer"));
        
        //check for ledges
        if (flying){
            if(!flight_player->is_playing())
                flight_player->play();
        }
        else {
            if(flight_player->is_playing())
                flight_player->stop();
        }
        
        Input *event = Input::get_singleton();
        if(event->is_action_pressed("pickup_item")) {
            String sound = should_play_fail ? "./FailSound" : 
              "./FlightPickupSound";
            const char *sound2 = should_play_fail ? "./FailSound" : 
              "./FlightPickupSound";
            std::cout << "in physics " << should_play_fail  << " " <<
               sound2 <<
            std::endl;
            AudioStreamPlayer *player = 
              cast_to<AudioStreamPlayer>(get_node((NodePath)sound));
            if(!player->is_playing())
                player->play();
            if(!should_play_fail && !player->is_playing())
                should_play_fail = true;
        }
    
        int temp = 0;
        if(event->is_action_pressed("ui_up")){
            temp = 1;
        }
        //back
        if(event->is_action_pressed("ui_down")){
                temp = 2;
        }
        //rotations
        if(event->is_action_pressed("ui_right"))
        {
          // set_rotation(get_rotation()+Vector3(0,-5*M_PI/180.0,0));
            temp = 3;
        }
        if(event->is_action_pressed("ui_left"))
        {
          temp = 4;
        }
        
        if(event->is_action_pressed("strafe_right"))
        {
             temp = 5;
        }
        if(event->is_action_pressed("strafe_left"))
        {
             temp = 6;
        }


         //flying, using wasd
         //default f
         if(event->is_action_just_pressed("toggle_fly"))
         {
             temp = 7;
         }

         //hang on ledge, or fall if already hanging
         //default ctrl
         if(event->is_action_just_pressed("fall_ledge")){
             temp = 8;
         }

         //move until back ray is no longer colliding,
         // and flip 180 to face ledge
         if(hangAnimInProgress){
             temp = 9;
         }

         //move until back ray is colliding, and pull up
         if(pullUpInProgress){
             temp = 10;
         }
        
        //data for peers to use
        //sets this slaves position for peers and 
        rset("slavePosition", get_translation());
        rset("slaveMovement", static_cast<int64_t>(temp));
        _moveCharacter(delta, temp);
    }
    else
    {
      //other players(slaves)
        _moveCharacter(delta,slaveMovement);
        set_translation(slavePosition);
    }

    if(get_tree()->is_network_server())
    {
        get_node("/root/Network")->call("update_position",
          get_name().to_int(), get_translation());
    }
}

//does actual movement for server/clients
void Player::_moveCharacter(float delta, int movement)
{
  if(!stunned) {
    if (flying){
      emit_signal("use_timer");
      translate(Vector3(0,0,-.3));
    }
    velocity += delta * gravity;
    //forward
    if(movement == 1){
      //pitch up if flying
      if (flying){
        set_rotation(get_rotation()+Vector3(1*M_PI/180.0,0,0));
      }
      //if grounded, or jumping player can move
      //can jump off ledges
      else if(ray1->is_colliding() || doubleJump >= 1){
        set_translation(get_translation()+direction*.1);
        if(stamina > 0)
          stamina -= .5;
        emit_signal("stamina_changed", stamina);
      }
      //on ledge if front ray isnt colliding and not jumping
      else if ((!ray1->is_colliding()) && doubleJump ==0){
        onLedge = true;
      } else {
        onLedge = false;
      }
    }
    //back
    if(movement == 2){
      if (flying){
        set_rotation(get_rotation()+Vector3(-1*M_PI/180.0,0,0));
      }else {
        if(ray2->is_colliding() || doubleJump >= 1)
          set_translation(get_translation()-direction*.1);
        if(stamina > 0)
          stamina -= .5;
        emit_signal("stamina_changed", stamina);
      }
    }
    //rotations
    if(movement == 3)
    {
      // set_rotation(get_rotation()+Vector3(0,-5*M_PI/180.0,0));
      Vector2 newDir = Vector2(direction.x,direction.z).rotated(.05);
      direction = Vector3(newDir.x,0,newDir.y).normalized();
      rotate(Vector3(0,-1,0), .05);
    }
    if(movement == 4)
    {
      // set_rotation(get_rotation()+Vector3(0,5*M_PI/180.0,0));
      Vector2 newDir = Vector2(direction.x,direction.z).rotated(-.05);
      direction = Vector3(newDir.x,0,newDir.y).normalized();
      rotate(Vector3(0,1,0), .05);
    }
    //strafing, q,e
    //will not stop at ledges
    if(movement == 5)
    {
      translate(Vector3(.25,0,0));
      if(stamina > 0)
          stamina -= .4;
      emit_signal("stamina_changed", stamina);
    }
    if(movement == 6)
    {
      translate(Vector3(-.25,0,0));
      if(stamina > 0)
          stamina -= .5;
      emit_signal("stamina_changed", stamina);
    }


    //flying, using wasd
    //default f
    if(movement == 7)
    {
      if (flying){
        //disable flight
        flying = false;
        gravity.y = -9.8;
        set_rotation(Vector3(0,get_rotation().y,get_rotation().z));
      } else {
        flying = true;
        velocity.y = 0;
        gravity.y = 0;
      }
    }

    //hang on ledge, or fall if already hanging
    //default ctrl
    if(movement == 8){
      if(hanging){
        hanging = false;
        gravity = Vector3(0,-9.8,0);
      } else if (!hanging && onLedge){
        hanging=true;
        onLedge = false;
        hangAnimInProgress = true;
        gravity = Vector3(0,0,0);
      }
    }

    //move until back ray is no longer colliding, and flip 180 to face ledge
    if(movement == 9){
      set_translation(get_translation()+direction*.1);
      
      if (!ray2->is_colliding()){
        translate(Vector3(-2,-2,0));
        Vector2 newDir = Vector2(direction.x,direction.z).rotated(M_PI);
        direction = Vector3(newDir.x,0,newDir.y).normalized();
        rotate(Vector3(0,-1,0), M_PI);
        hangAnimInProgress = false;
      }
    }

    //move until back ray is colliding, and pull up
    if(movement == 10){
      set_translation(get_translation()+direction*.1);
      
      if (ray2->is_colliding()){
        gravity = Vector3(0,-9.8,0);
        pullUpInProgress = false;
      }
    }

    velocity = move_and_slide(velocity,Vector3(0,-1,0));
    //reset jumps once landing
    if(doubleJump > 0 && velocity.y == 0.0)
      doubleJump = 0;
  }
    
}

//jump if grounded, pullup if hanging
void Player::_input(InputEvent *event){
  if(event->is_action_pressed("jump"))
  { 
    if (hanging){
      hanging = false;
      translate(Vector3(-2,2,0));
      pullUpInProgress = true;

    } else if(doubleJump < 2)
    {
      doubleJump += 1;
      velocity = velocity + Vector3(0,7,0);
    } 

  }

}

void Player::_on_area_entered(Area *area) {
  Node *parent = area->get_parent();
  if(parent->get_name().to_lower().find("stamina") != -1) {
    cast_to<AudioStreamPlayer>(get_node("./StaminaPickupSound"))->play();
  }
  else if(parent->get_name().to_lower().find("flight") != -1) {
    should_play_fail = false;
    std::cout << "In area entered " << should_play_fail << std::endl;
  }
  else if(parent->get_name().to_lower().find("ai") != -1) {
    stunned = true;
    emit_signal("use_timer");
    emit_signal("stunned");
  }
}

void Player::_on_area_exited(Area *area) {
}

void Player::_on_timer_up() {
  std::cout << "timer up!" << std::endl;
  if(stunned) {
    stunned = false;
  }
  flying = false;
  gravity[1] = -9.8;
  set_rotation(Vector3(0,get_rotation().y,get_rotation().z));
  AudioStreamPlayer *player = cast_to<AudioStreamPlayer>(get_node("./FlyingPlayer"));
  if(player->is_playing())
    player->stop();
}

void Player::_process(float delta) {
}

void Player::init(String nickname, Vector3 startPosition, bool isSlave)
{
    //static_cast<Label*>(get_node("GUI/Nickname"))->set_text(nickname);
    set_translation(startPosition);
    //if(isSlave)
    //{
    //    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    //    static_cast<Sprite*>(get_node("Sprite"))->set_texture(resourceLoader->load("res://player/player-alt.png"));
    //}
}
