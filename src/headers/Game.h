
#include "MainWindow.h"

struct SharedContent{

    std::shared_ptr<MainWindow> window;
    //add other shared stuff here

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