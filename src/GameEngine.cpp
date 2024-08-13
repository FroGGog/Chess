#include "headers/GameEngine.h"

GameEngine::GameEngine(std::shared_ptr<GameWorld> gWorld_, std::shared_ptr<EntityManager> e_manager_)
{
	gWorld = gWorld_;
	e_manager = e_manager_;

	mouseCollider.setSize(sf::Vector2f{ 1.f,1.f });
	mouseCollider.setFillColor(sf::Color::Red);
}

void GameEngine::Update(std::shared_ptr<MainWindow> win)
{
	updateMouseBox(win);

}

//private scope
void GameEngine::updateMouseBox(std::shared_ptr<MainWindow> win)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i temp = sf::Mouse::getPosition(win->getWindow());
		mouseCollider.setPosition(sf::Vector2f{ float(temp.x), float(temp.y) });
		checkMouseBoxColl();
	}

}

void GameEngine::checkMouseBoxColl()
{
	for (auto iter{ e_manager->getEntities().begin() }; iter < e_manager->getEntities().end(); iter++) {
		iter->setClicked(false);
	}

	for (auto iter{ e_manager->getEntities().begin() }; iter < e_manager->getEntities().end(); iter++) {
		if (mouseCollider.getGlobalBounds().intersects(iter->getSprite().getGlobalBounds())) {
			iter->setClicked(true);
		}
		
	}


}
