#include "stdafx.h"

#include "headers/GameWorld.h"

//public scope
GameWorld::GameWorld(sf::Vector2u winSize_){

    bgColor = sf::Color{40, 40, 40, 255};
    winSize = winSize_;

    CreateFieldTiles();

}

void GameWorld::render(std::shared_ptr<MainWindow> win){

    for (auto iter{ gameField.begin() }; iter < gameField.end(); iter++) {
        for (auto iter2{ iter->begin() }; iter2 < iter->end(); iter2++) {
            win->Draw(*iter2);
        }
        
    }

}


//getter and setters

sf::Color GameWorld::getBGColor() const{

    return bgColor;

}

std::vector<std::vector<sf::RectangleShape>>& GameWorld::getGField()
{
    return gameField;
}

void GameWorld::CreateFieldTiles(){

    bool firstTile = true;
    bool black = false;

    float pos_y = 0.f;

    // set margin for game board
    float x_margin = 64.f;
    float y_margin = 32.f;

    std::vector<sf::RectangleShape> rowV;

    for(unsigned row{0}; row < 8; row++){
        rowV.clear();
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
                temp.setPosition(sf::Vector2f{ x_margin + col * 64, pos_y});
            }

            rowV.push_back(temp);

        }
        gameField.push_back(rowV);
        black = !black;
        pos_y = gameField[row].back().getPosition().y + 64.f;
    }

}
