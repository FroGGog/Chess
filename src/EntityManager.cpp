#include "stdafx.h"

#include "headers/EntityManager.h"

//private scope
void Entity::setupSprite()
{
	// cuts rect from main texture and get sprite for current piece
	int fig_id = 5;

	switch (type)
	{
	case FigureType::PAWN:
		fig_id = 5;
		break;
	case FigureType::KNIGHT:
		fig_id = 3;
		break;
	case FigureType::BISHOP:
		fig_id = 4;
		break;
	case FigureType::ROOK:
		fig_id = 2;
		break;
	case FigureType::QUEEN:
		fig_id = 0;
		break;
	case FigureType::KING:
		fig_id = 1;
		break;
	default:
		break;
	}

	if (isWhite) {
		e_sprite.setTextureRect(sf::IntRect{ 60 * fig_id, 60 , 60, 60 });
	}
	else {
		e_sprite.setTextureRect(sf::IntRect{ 60 * fig_id, 0, 60, 60 });
	}
	

}

//public scope
Entity::Entity(sf::Texture& texture, unsigned xBoard, unsigned yBoard, FigureType type_, bool white) {

	e_sprite.setTexture(texture);
	type = type_;
	isWhite = white;

	setupSprite();

	isClicked = false;

	pos.x = xBoard;
	pos.y = yBoard;

}

sf::Sprite& Entity::getSprite()
{
	return e_sprite;
}

sf::Vector2u Entity::getPos() const
{
	return sf::Vector2u(pos.x, pos.y);
}

FigureType Entity::getType() const
{
	return type;
}

void Entity::setClicked(bool switcher)
{
	isClicked = switcher;
}


//EntiyManager class stuff

//private scope
void EntityManager::setupEntities()
{
	bool drawWhite = true;

	unsigned pos_x = 0;
	unsigned pos_y = 0;

	int counter = 0;

	FigureType currentType = FigureType::ROOK;
	bool reverse = false;

	//main loop for adding non pawn pieces
	for (unsigned repeat{ 0 }; repeat < 16; repeat++) {
		
		if (drawWhite) {
			pos_x = 7;
		}
		else {
			pos_x = 0;
		}

		Entity temp{ allPiecesTexture, pos_x, pos_y, currentType, drawWhite };
		
		allEntities.push_back(temp);

		drawWhite = !drawWhite;

		counter++;

		if (counter >= 2) {
			pos_y++;
			counter = 0;
			
			switch (currentType)
			{
			case FigureType::PAWN:
				break;
			case FigureType::KNIGHT:
				if (reverse) {
					currentType = FigureType::ROOK;
				}
				else {
					currentType = FigureType::BISHOP;
				}
				break;
			case FigureType::BISHOP:
				if (reverse) {
					currentType = FigureType::KNIGHT;
				}
				else{
					currentType = FigureType::QUEEN;
				}
				break;
			case FigureType::ROOK:
				currentType = FigureType::KNIGHT;
				break;
			case FigureType::QUEEN:
				currentType = FigureType::KING;
				break;
			case FigureType::KING:
				reverse = true;
				currentType = FigureType::BISHOP;
				break;
			default:
				break;
			}
		}
	}

	currentType = FigureType::PAWN;


	// TODO: add all in one for loop
	pos_x = 1;
	pos_y = 0;

	//loop for adding pawns black pawn
	for (unsigned repeat{ 0 }; repeat < 8; repeat++) {

		Entity temp{ allPiecesTexture, pos_x, pos_y, currentType, drawWhite =false};

		pos_y++;

		allEntities.push_back(temp);

	}

	pos_x = 6;
	pos_y = 0;
	//loop for adding white pawns
	for (unsigned repeat{ 0 }; repeat < 8; repeat++) {

		Entity temp{ allPiecesTexture, pos_x, pos_y, currentType, true };

		pos_y++;

		allEntities.push_back(temp);

	}


}

void EntityManager::LoadTexture() {

	if (!allPiecesTexture.loadFromFile("ChessPiecesArray.png")) {
		std::cerr << "ERROR::LOADFROMFILE::CHESSARRAY.png\n";
	}

}


//public scope
EntityManager::EntityManager()
{
	LoadTexture();

	setupEntities();

}

void EntityManager::render(std::shared_ptr<MainWindow> win, std::shared_ptr<GameWorld> g_world)
{

	for (auto iter{ allEntities.begin() }; iter < allEntities.end(); iter++) {

		iter->getSprite().setPosition(g_world->getGField()[iter->getPos().x][iter->getPos().y].getPosition());

		win->Draw(iter->getSprite());
	}
	printData = false;

}

std::vector<Entity>& EntityManager::getEntities()
{
	return allEntities;
}
