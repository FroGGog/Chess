#include "stdafx.h"

#include "headers/GameWorld.h"

//public scope
GameWorld::GameWorld(sf::Vector2u winSize_){

    bgColor = sf::Color{40, 40, 40, 255};
    winSize = winSize_;

    LoadTexture();

    CreateFieldTiles();

}

void GameWorld::render(std::shared_ptr<MainWindow> win){

    for (auto iter{ gameField.begin() }; iter < gameField.end(); iter++) {
        win->Draw(*iter);
    }

}


//getter and setters

sf::Color GameWorld::getBGColor() const{

    return bgColor;

}

void GameWorld::CreateFieldTiles(){

    bool firstTile = true;
    bool black = false;

    float pos_y = 0.f;

    // set margin for game board
    float x_margin = 64.f;
    float y_margin = 32.f;

    for(unsigned row{0}; row < 8; row++){

        for(unsigned col{0}; col < 8; col++){

            sf::RectangleShape temp{ sf::Vector2f{64.f, 64.f} };
            if (black) {
                temp.setFillColor(sf::Color{119, 149, 86, 255});
                black = !black;
            }
            else {
                temp.setFillColor(sf::Color{ 235, 236, 208, 255 });
                black = !black;
            }
            
            if (firstTile) {
                temp.setPosition(sf::Vector2f{ x_margin, y_margin});
                pos_y = temp.getPosition().y;
                firstTile = false;
                
            }
            else {
                temp.setPosition(sf::Vector2f{ gameField.front().getPosition().x + col * 64, pos_y});
            }

            gameField.push_back(temp);

        }
        black = !black;
        pos_y = gameField.back().getPosition().y + 64.f;
    }

}

// TODO : maybe load texture in another class
// private scope
bool GameWorld::LoadTexture(){

    //piece size 60x60
    if(!allPiecesTexture.loadFromFile("ChessPiecesArray.png")){
        std::cerr << "ERROR::LOADFROMFILE::CHESSARRAY.png\n";
        return false;
    }
    return true;

}
