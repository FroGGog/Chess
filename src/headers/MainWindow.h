
class MainWindow{

private:

    //all window private vars
    sf::RenderWindow win;
    sf::VideoMode vidMode;
    std::string title;

    bool isOpen_v;

    void Create();
    void Destroy();

public:

    MainWindow(const std::string title_, sf::Vector2u winSize);

    void Update();
    void startRender(sf::Color bgColor_);
    void endRender();

    void Draw(sf::Drawable& drawbleItemd);

    //getters and setters
    sf::Vector2u getWinSize();
    void setWinResol(sf::Vector2u newResol_);
    bool isOpen();

};