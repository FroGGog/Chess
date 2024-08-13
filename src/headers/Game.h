#pragma once

#include "GameWorld.h"
#include "EntityManager.h"


struct SharedContent{

    std::shared_ptr<MainWindow> window;
    //add other shared stuff here
    std::shared_ptr<GameWorld> gWorld;
    std::shared_ptr<EntityManager> e_manager;

};

class Game{

private:

    SharedContent content;

public:

    Game(std::string title_, sf::Vector2u vidMode);

    void Update();
    void Render();

    //getters and setters
    std::shared_ptr<MainWindow> getWindow() const;

};