#include "MainWindow.h"

//base GameWorld class - draw all stuf using it, also hold all used resources
class GameWorld{

private:

    sf::Texture allPiecesTexture;
    sf::Color bgColor;
    sf::Vector2u winSize;

    std::deque<sf::RectangleShape> gameField;

    bool LoadTexture();

    void CreateFieldTiles();

public:

    GameWorld(sf::Vector2u winSize_);

    sf::Color getBGColor() const;

    void render(std::shared_ptr<MainWindow> win);

};

