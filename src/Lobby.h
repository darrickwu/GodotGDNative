#ifndef LOBBY_H
#define LOBBY_H

#include <Godot.hpp>
#include <Node.hpp>

namespace godot {

class Lobby : public Node {
    GODOT_CLASS(Lobby, Node)

public:
    static void _register_methods();

    Lobby();
    ~Lobby();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _on_start_pressed();
};
}
#endif
