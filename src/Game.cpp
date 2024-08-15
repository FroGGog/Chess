#include "stdafx.h"

#include "headers/Game.h"


Game::Game(std::string title_, sf::Vector2u vidMode)
{

    content.window = std::make_shared<MainWindow>(title_, vidMode);
    content.gWorld = std::make_shared<GameWorld>(content.window->getWinSize());
    content.e_manager = std::make_shared<EntityManager>();
    content.gameEngine = std::make_shared<GameEngine>(content.gWorld, content.e_manager);

}

void Game::Update(){

    content.window->Update();

    content.gameEngine->Update(content.window);
}

void Game::Render(){

    content.window->startRender(content.gWorld->getBGColor());

    //draw all stuff here
    content.gWorld->render(content.window);
    content.e_manager->render(content.window, content.gWorld);
    content.gameEngine->render(content.window);

    content.window->endRender();

}

//getters and setters

std::shared_ptr<MainWindow> Game::getWindow() const{
    return content.window;
}