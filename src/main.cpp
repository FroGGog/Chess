#include "stdafx.h"

#include "headers/Game.h"


int main(){

    Game game{"Chess", sf::Vector2u{800, 600}};

    while(game.getWindow()->isOpen()){

        game.Update();

        game.Render();

    }
    return 0;


}