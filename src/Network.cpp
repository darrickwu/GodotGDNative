#include "Network.h"
#include <SceneTree.hpp>
#include <NetworkedMultiplayerENet.hpp>
#include <ResourceLoader.hpp>
#include <Player.h>

using namespace godot;
using namespace std;

void Network::_register_methods() {
    register_method("_process", &Network::_process);
    register_method("_ready", &Network::_ready);
    register_method("create_server", 
        &Network::create_server, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("connect_to_server", 
        &Network::connect_to_server, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_connected_to_server", 
        &Network::_connected_to_server, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_on_player_disconnected", 
        &Network::_on_player_disconnected, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_on_player_connected", 
        &Network::_on_player_connected, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_request_player_info", 
        &Network::_request_player_info, GODOT_METHOD_RPC_MODE_REMOTE);
    register_method("_request_players", 
        &Network::_request_players, GODOT_METHOD_RPC_MODE_REMOTE);
    register_method("_send_player_info", 
        &Network::_send_player_info, GODOT_METHOD_RPC_MODE_REMOTE);
    register_method("update_position", 
        &Network::update_position, GODOT_METHOD_RPC_MODE_DISABLED);

    register_property<Network, Dictionary>("selfData", &Network::selfData,
        Dictionary(), GODOT_METHOD_RPC_MODE_DISABLED);
    register_property<Network, Dictionary>("players", &Network::players, 
        Dictionary(), GODOT_METHOD_RPC_MODE_DISABLED);
}

Network::Network() {
}

Network::~Network() {
    // add your cleanup here
}

void Network::_init() {
    selfData["name"] = "";
    //player spawnpoint
    selfData["translation"] = Vector3(-60,12,-4.5);
}
void Network::_ready() {
    get_tree()->connect("network_peer_disconnected",
         this, "_on_player_disconnected");
    //get_tree()->connect("network_peer_connected", this, "_on_player_connected");
}

void Network::_process(float delta) {
}

void Network::create_server(String playerNickname)
{
     selfData["name"] = playerNickname;
     players[1] = selfData;
     NetworkedMultiplayerENet* peer = NetworkedMultiplayerENet::_new();
     //peer->set_bind_ip("*");
     peer->create_server(SERVER_PORT, MAX_PLAYERS);
     get_tree()->set_network_peer(peer);
}

void Network::connect_to_server(String playerNickname)
{
    selfData["name"] = playerNickname;
    get_tree()->connect("connected_to_server", this, "_connected_to_server");
    NetworkedMultiplayerENet* peer = NetworkedMultiplayerENet::_new();
    peer->create_client(SERVER_IP, SERVER_PORT);
    get_tree()->set_network_peer(peer);
}

void Network::_connected_to_server()
{
    int64_t localPlayerId = get_tree()->get_network_unique_id();
    players[localPlayerId] = selfData;
    rpc("_send_player_info", localPlayerId, selfData);
}

void Network::_on_player_disconnected(int64_t id)
{
    players.erase(id);
}

//triggered by all the peers
void Network::_on_player_connected(int64_t connectedPlayerId)
{
    Godot::print( "Player connected to server" );
    int64_t localPlayerId = get_tree()->get_network_unique_id();
    if(!get_tree()->is_network_server())
    {
        //tell the server to request the new guys info
        rpc_id(1, "_request_player_info", localPlayerId, connectedPlayerId);
    }
}

void Network::_request_player_info(int64_t requestFromId, int64_t playerId)
{
    if(get_tree()->is_network_server())
    {
        //server will send playerId info to whoever requestFromId
        //will avoid the server specific loop in sendplayerinfo
        Godot::print("requesting player info");
        rpc_id(requestFromId, "_send_player_info", playerId, 
            players[playerId]);
    }
}

//who calls this?
void Network::_request_players(int64_t requestFromId)
{
    if(get_tree()->is_network_server())
    {
        for(int64_t peerId = 0; peerId < players.size(); peerId++)
        {
            if(peerId != requestFromId)
            {
                rpc_id(requestFromId, "_send_player_info", peerId, 
                    players[peerId]);
            }
        }
    }
}

//id is THEM
void Network::_send_player_info(int64_t id, Dictionary info)
{
    if(get_tree()->is_network_server())
    {
        //send this peers info to all other peers
        for(int64_t peerId = 1; peerId < players.size(); peerId++)
        {   
            if(peerId != id){
                //peerIds already exist
                //id is the new guy
                //peerId must set up on id
                //setup peerId on id ie setup server on client
                //(they can see me)
               rpc_id(id, "_send_player_info", peerId, players[peerId]);
            }
        }
    }
    //setup the player(could be other peers, setting up for you)
    //(i can see them)
    players[id] = info;
    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    PlayerScene = resourceLoader->load("res://Player.tscn");
    godot::Player* player = 
        static_cast<godot::Player*>(PlayerScene->instance());
    player->set_name(String(id));
    player->set_network_master(id);
    get_node("/root/Game")->add_child(player);
    
    player->init(info["name"], info["translation"], false);
}

void Network::update_position(int64_t id, Vector3 position)
{
    Dictionary playerInfo = players[id];
    playerInfo["translation"] = position;
}


