#include "MultiPlayerMenu.h"
#include <stdlib.h>
#include <stdio.h>
#include <Input.hpp>
#include <SceneTree.hpp>
#include <ResourceLoader.hpp>
#include <Engine.hpp>
#include <ClassDB.hpp>
#include <ProjectSettings.hpp>
#include <TextEdit.hpp>
using namespace godot;

void MultiPlayerMenu::_register_methods() {
    register_method("_process", &MultiPlayerMenu::_process);
    register_method("_ready", &MultiPlayerMenu::_ready);
    register_method("_on_Create_pressed",&MultiPlayerMenu::_on_Create_pressed);
    register_method("_on_Join_pressed",&MultiPlayerMenu::_on_Join_pressed);
}

MultiPlayerMenu::MultiPlayerMenu() {
}

MultiPlayerMenu::~MultiPlayerMenu() {
    // add your cleanup here
}

void MultiPlayerMenu::_init() {
}
void MultiPlayerMenu::_ready() {
    get_node("./Buttons/CreateServer")->connect("pressed",this,"_on_Create_pressed");
    get_node("./Buttons/JoinServer")->connect("pressed",this,"_on_Join_pressed");    
}

void MultiPlayerMenu::_process(float delta) {
}

void MultiPlayerMenu::_on_Create_pressed(){
    String name = cast_to<TextEdit>(get_node("./NameInput"))->get_text();
    Godot::print(name);
    
    get_node("/root/Network")->call("create_server", name);
    this->get_tree()->change_scene("res://main.tscn");
}
void MultiPlayerMenu::_on_Join_pressed(){
    String name = cast_to<TextEdit>(get_node("./NameInput"))->get_text();
    Godot::print(name);
    get_node("/root/Network")->call("connect_to_server", name);
    this->get_tree()->change_scene("res://main.tscn");
}

