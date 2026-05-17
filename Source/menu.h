#include "game.h"
class Menu {
public:

    Sprite background; Font font; SoundBuffer buffer;
    Texture bg_texture;
    Menu();
    void display_menu();
    void display_menu1()
    {
        Game g;
        g.start_game();
    }



};

