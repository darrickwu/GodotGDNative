#include "MainMenu.h"
#include <stdlib.h>
#include <stdio.h>
#include <Input.hpp>
#include <SceneTree.hpp>
using namespace godot;

void MainMenu::_register_methods() {
    register_method("_process", &MainMenu::_process);
    register_method("_ready", &MainMenu::_ready);
    register_method("_on_SinglePlayer_pressed",&MainMenu::_on_SinglePlayer_pressed);
    register_method("_on_Multiplayer_pressed",&MainMenu::_on_Multiplayer_pressed);
}

MainMenu::MainMenu() {
}

MainMenu::~MainMenu() {
    // add your cleanup here
}

void MainMenu::_init() {
}
void MainMenu::_ready() {
    get_node("./Buttons/SinglePlayer")->connect("pressed",this,"_on_SinglePlayer_pressed");
    get_node("./Buttons2/Multiplayer")->connect("pressed",this,"_on_Multiplayer_pressed");
    
}

void MainMenu::_process(float delta) {
}
void MainMenu::_on_SinglePlayer_pressed(){
    get_node("/root/Network")->call("create_server", name);
    this->get_tree()->change_scene("res://main.tscn");
}
void MainMenu::_on_Multiplayer_pressed(){
    //get_node("/root/Network")->call("create_server", name);
    this->get_tree()->change_scene("res://MultiPlayer.tscn");
}

