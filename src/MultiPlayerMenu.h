#ifndef MultiPlayerMenu_H
#define MultiPlayerMenu_H

#include <Godot.hpp>
#include <Button.hpp>

namespace godot {

class MultiPlayerMenu : public Button {
    GODOT_CLASS(MultiPlayerMenu, Button)
private:
    String name;
public:
    static void _register_methods();

    MultiPlayerMenu();
    ~MultiPlayerMenu();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _on_Create_pressed();
    void _on_Join_pressed();
};
}
#endif
