
#include "GameWorld.h"
#include "EntityManager.h"


class GameEngine {

private:

	std::shared_ptr<GameWorld> gWorld;
	std::shared_ptr<EntityManager> e_manager;

	sf::RectangleShape mouseCollider;

	void updateMouseBox(std::shared_ptr<MainWindow> win);
	void checkMouseBoxColl();


public: 

	GameEngine(std::shared_ptr<GameWorld> gWorld_, std::shared_ptr<EntityManager> e_manager_);

	void Update(std::shared_ptr<MainWindow> win);

	void render(std::shared_ptr<MainWindow> win);

};