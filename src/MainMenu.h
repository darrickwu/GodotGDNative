#ifndef MainMenu_H
#define MainMenu_H

#include <Godot.hpp>
#include <Button.hpp>

namespace godot {

class MainMenu : public Button {
    GODOT_CLASS(MainMenu, Button)
private:
    String name;
public:
    static void _register_methods();

    MainMenu();
    ~MainMenu();

    void _init(); // our initializer called by Godot
    void _ready(); 
    void _process(float delta);
    void _on_SinglePlayer_pressed();
    void _on_Multiplayer_pressed();
};
}
#endif
