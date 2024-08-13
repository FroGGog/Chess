#include "stdafx.h"

#include "headers/MainWindow.h"

MainWindow::MainWindow(const std::string title_, sf::Vector2u winSize)
{

    vidMode.width = winSize.x;
    vidMode.height = winSize.y;
    title = title_;
    isOpen_v = true;

    Create();

}

void MainWindow::Update(){

    sf::Event event;

    while(win.pollEvent(event)){

        switch (event.type)
        {
        case sf::Event::Closed:
            isOpen_v = false;
            Destroy();
            break;

        case sf::Event::KeyPressed:
            // maybe fullscrenn mode
            
            break;

        default:
            break;
        }

    }


}

void MainWindow::startRender(sf::Color bgColor_){

    win.clear(bgColor_);

}

void MainWindow::endRender(){

    win.display();

}

void MainWindow::Draw(sf::Drawable& drawableItem){

    win.draw(drawableItem);

}

void MainWindow::Create(){

    auto style = sf::Style::Titlebar | sf::Style::Close;

    win.create(vidMode, title, style);

    win.setFramerateLimit(10);

}

void MainWindow::Destroy(){
    win.close();
}

//getters and setters

sf::Vector2u MainWindow::getWinSize(){

    return sf::Vector2u{vidMode.width, vidMode.height};
}

void MainWindow::setWinResol(sf::Vector2u newResol_){

    vidMode.width = newResol_.x;
    vidMode.height = newResol_.y;

    Destroy();
    Create();

}

bool MainWindow::isOpen(){

    return isOpen_v;

}

sf::RenderWindow& MainWindow::getWindow()
{
    return win;
}
