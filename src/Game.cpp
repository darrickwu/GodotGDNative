#include "Game.h"
#include <ResourceLoader.hpp>
#include <SceneTree.hpp>
#include "Player.h"
#include <Dictionary.hpp>
#include "StaminaBar.h"
#include "Timer.h"

using namespace godot;
using namespace std;

void Game::_register_methods()
{
    register_method("_init", &Game::_init, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_ready", &Game::_ready, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_on_player_disconnected", &Game::_on_player_disconnected, 
        GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_on_server_disconnected", &Game::_on_server_disconnected, 
        GODOT_METHOD_RPC_MODE_DISABLED);
}

Game::Game()
{

}

Game::~Game()
{

}

void Game::_init()
{
    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    PlayerScene = resourceLoader->load("res://Player.tscn");
}

//setup the player(for yourself, not for others)
void Game::_ready()
{
    cout << "in ready in game.cpp" << endl;
    get_tree()->connect("network_peer_disconnected", this, "_on_player_disconnected");
    get_tree()->connect("server_disconnected", this, "_on_server_disconnected");
    
    godot::Player* player = static_cast<godot::Player*>(PlayerScene->instance());

    player->set_name(String(get_tree()->get_network_unique_id()));
    player->set("nodeName", get_tree()->get_network_unique_id());
    player->set_network_master(get_tree()->get_network_unique_id());
    add_child(player);
    //THIS MIGHT BREAK MULTIPLAYER
    player->set_name("localPlayer");
    //Godot::print(player->get_name());
    cast_to<StaminaBar>(get_node("./StaminaBar"))->
        connect_stamina_signal(cast_to<Node>(player));
    cast_to<Timer>(get_node("./Timer"))->
        connect_timer_signal(cast_to<Node>(player));
    Dictionary selfData = Dictionary(get_node("/root/Network")->get("selfData"));
    player->init(selfData["name"], selfData["translation"], false);
    cast_to<AudioStreamPlayer>(get_node("./BackgroundMusic"))->play();
}

void Game::_on_player_disconnected(int64_t id)
{
    if(get_node((NodePath)String(id)))
    {
        get_node((NodePath)String(id))->queue_free();
    }
}

void Game::_on_server_disconnected(int64_t id)
{
    get_tree()->change_scene("res://TitleScreen.tscn");
}
