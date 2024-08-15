#pragma once

#include "MainWindow.h"
#include "GameWorld.h"

struct posOnBoard {

	unsigned x;
	unsigned y;

	posOnBoard() : x(0), y(0) {};

};

enum class FigureType{PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};

class Entity {

private:

	sf::Sprite e_sprite;

	bool isClicked;
	bool isWhite;

	posOnBoard pos;

	FigureType type;
	std::string stringType;

	void setupSprite();

public:

	Entity(sf::Texture& texture, unsigned xBoard, unsigned uBoard, FigureType type_, bool white = true);

	//gettes
	sf::Sprite& getSprite();
	sf::Vector2u getPos() const;
	FigureType getType() const;
	bool getClicked() const;
	bool getColor() const;
	std::string getStringType() const;
	//setters
	void setClicked(bool switcher);
	void setPosition(unsigned x_, unsigned y_);

};

class EntityManager {

private:

	std::vector<Entity> allEntities;

	sf::Texture allPiecesTexture;

	sf::RectangleShape choosedRect;

	bool printData;

	void setupEntities();

	void LoadTexture();

public:

	EntityManager();

	void render(std::shared_ptr<MainWindow> win, std::shared_ptr<GameWorld> g_world);

	//getters
	std::vector<Entity>& getEntities();

};