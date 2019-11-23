//#include "Character.h"
#include "Player.h"
#include "StaminaRefill.h"
#include "Flight.h"
#include "StaminaBar.h"
#include "CameraRay.h"
#include "Timer.h"
#include "PowerUpSound.h"
#include "MainMenu.h"
#include "Network.h"
#include "MultiPlayerMenu.h"
//#include "Lobby.h"
#include "Game.h"
#include "ShootingAI.h"
#include "StunAI.h"
#include "SpawnPoint.h"
#include "Bullet.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    //godot::register_class<godot::Character>();
    godot::register_class<godot::Player>();
    godot::register_class<godot::StaminaRefill>();
    godot::register_class<godot::Flight>();
    godot::register_class<godot::StaminaBar>();
    godot::register_class<godot::CameraRay>();
    godot::register_class<godot::Timer>();
    godot::register_class<godot::PowerUpSound>();
    godot::register_class<godot::MainMenu>();
    godot::register_class<godot::Network>();
    godot::register_class<godot::MultiPlayerMenu>();
    //godot::register_class<godot::Lobby>();
    godot::register_class<godot::Game>();
    godot::register_class<godot::ShootingAI>();
    godot::register_class<godot::StunAI>();
    godot::register_class<godot::SpawnPoint>();
    godot::register_class<godot::Bullet>();
}
