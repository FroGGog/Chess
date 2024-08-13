#pragma once

#include "MainWindow.h"

//base GameWorld class - draw all stuf using it, also hold all used resources
class GameWorld{

private:

    sf::Color bgColor;
    sf::Vector2u winSize;

    std::vector<std::vector<sf::RectangleShape>> gameField;

    void CreateFieldTiles();

public:

    GameWorld(sf::Vector2u winSize_);

    sf::Color getBGColor() const;
    std::vector<std::vector<sf::RectangleShape>>& getGField();

    void render(std::shared_ptr<MainWindow> win);

};

