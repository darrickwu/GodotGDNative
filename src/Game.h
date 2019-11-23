#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <Ref.hpp>
#include <PackedScene.hpp>

namespace godot
{

class Game : public Node
{
    GODOT_CLASS(Game, Node)

public:
    static void _register_methods();

    Game();
    ~Game();

    void _init();
    void _ready();
    void _on_player_disconnected(int64_t id);
    void _on_server_disconnected(int64_t id);

private:
    Ref<PackedScene> PlayerScene;

};

}
