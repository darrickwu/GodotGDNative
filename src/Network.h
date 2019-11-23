#ifndef Network_H
#define Network_H

#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>
namespace godot {

class Network : public Node {
    GODOT_CLASS(Network, Node)

private:
    Dictionary selfData;
    Dictionary players;
    const String SERVER_IP = "127.0.0.1";
    const int64_t SERVER_PORT = 31400;
    const int64_t MAX_PLAYERS = 5;
    Ref<PackedScene> PlayerScene;

public:
    static void _register_methods();

    Network();
    ~Network();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void create_server(String playerNickname);
    void connect_to_server(String playerNickname);
    void _connected_to_server();
    void _on_player_disconnected(int64_t id);
    void _on_player_connected(int64_t connectedPlayerId);
    void _request_player_info(int64_t requestFromId, int64_t playerId);
    void _request_players(int64_t requestFromId);
    void _send_player_info(int64_t id, Dictionary info);
    void update_position(int64_t id, Vector3 translation);

    //network_peer_connected	
    //Emitted whenever this SceneTree’s network_peer connects with a new peer.	
    //ID is the peer ID of the new peer. Clients get notified when other	
    //clients connect to the same server. Upon connecting to a server, a 	
    //client also receives this signal for the server (with ID being 1).	
    // ^ is connected to on_player_connected	

    //server:	
    //create_server	
    //_on_player_connected	
    //_request_player_info	
    //send_player_info	

    //player:	
    //connect_to_server	
    //once network peer connects to server, _connected_to_server is called	
    //_send_player_info	
    //	
    //_on_player_connected
};
}
#endif
