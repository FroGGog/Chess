#include "headers/GameEngine.h"

GameEngine::GameEngine(std::shared_ptr<GameWorld> gWorld_, std::shared_ptr<EntityManager> e_manager_)
{
	gWorld = gWorld_;
	e_manager = e_manager_;

	choosedPiece = nullptr;

	mouseCollider.setSize(sf::Vector2f{ 1.f,1.f });
	mouseCollider.setFillColor(sf::Color::Red);

	convertedGField = {
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " "},
	};

	convertChessBoard();
}

GameEngine::~GameEngine()
{
	choosedPiece = nullptr;
}

void GameEngine::Update(std::shared_ptr<MainWindow> win)
{
	updateMouseBox(win);

	// TODO : call it only when something moved (convertChessBoard)
	

}

void GameEngine::render(std::shared_ptr<MainWindow> win)
{
	for (auto& posMove : possibleMoves) {
		win->Draw(posMove.getShape());
	}
}

//private scope
void GameEngine::updateMouseBox(std::shared_ptr<MainWindow> win)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i temp = sf::Mouse::getPosition(win->getWindow());
		mouseCollider.setPosition(sf::Vector2f{ float(temp.x), float(temp.y) });
		checkMovePiece();
		checkChoosedPiece();
	}

}

void GameEngine::checkChoosedPiece()
{
	//set current active to false
	if (choosedPiece != nullptr) {
		possibleMoves.clear();
		choosedPiece->setClicked(false);
	}

	for (auto iter{ e_manager->getEntities().begin() }; iter < e_manager->getEntities().end(); iter++) {
		if (mouseCollider.getGlobalBounds().intersects(iter->getSprite().getGlobalBounds())) {
			iter->setClicked(true);
			choosedPiece = &(*iter);
			calcPossMoves();
			break;
		}
		
	}


}

void GameEngine::checkMovePiece()
{
	if (possibleMoves.empty()) {
		return;
	}

	// TODO : change way how piece change position
	//check if player clicked on tile and want's to move piece
	for (auto iter{ possibleMoves.begin() }; iter < possibleMoves.end(); iter++) {
		if (mouseCollider.getGlobalBounds().intersects(iter->onTile.getGlobalBounds())) {
			std::cout << iter->onTile.getPosition().x / 64 - 1 << " " << iter->onTile.getPosition().y / 32 - 1;
			choosedPiece->setPosition(iter->onTile.getPosition().x / 64 - 1, iter->onTile.getPosition().y / 32 - 1);
			choosedPiece->setClicked(false);
			choosedPiece = nullptr;
			possibleMoves.clear();
			break;
		}
	}

}

void GameEngine::convertChessBoard()
{

	for (auto iter{ e_manager->getEntities().begin() }; iter < e_manager->getEntities().end(); iter++) {

		convertedGField[iter->getPos().x][iter->getPos().y] = iter->getStringType();

	}

	for (auto& i : convertedGField) {
		for (auto& j : i) {
			std::cout << j << ' ';
		}
		std::cout << "\n";
	}

}

void GameEngine::calcPossMoves()
{
	switch (choosedPiece->getType())
	{
	case FigureType::PAWN:
		pawnMoves();
		break;
	case FigureType::KNIGHT:
		break;
	case FigureType::BISHOP:
		break;
	case FigureType::ROOK:
		break;
	case FigureType::QUEEN:
		break;
	case FigureType::KING:
		break;
	default:
		break;
	}


}

void GameEngine::pawnMoves()
{
	sf::Vector2f pos;
	sf::Vector2f size;

	if (choosedPiece->getColor()) {
		for (unsigned i{ 1 }; i <= 2; i++) {
			if (convertedGField[choosedPiece->getPos().x - i][choosedPiece->getPos().y] == " ") {
				// get these to center circles
				pos = gWorld->getGField()[choosedPiece->getPos().x - i][choosedPiece->getPos().y].getPosition();
				size = gWorld->getGField()[choosedPiece->getPos().x - i][choosedPiece->getPos().y].getLocalBounds().getSize();
				
				// possible move has link to tile on which it is
				PossibleMove temp{gWorld->getGField()[choosedPiece->getPos().x - i][choosedPiece->getPos().y] };
				temp.setPosition(sf::Vector2f{pos.x + size.x / 2, pos.y + size.y / 2});
				possibleMoves.push_back(temp);
			}
		}
	}


}



// Possible move stuff here
PossibleMove::PossibleMove(sf::RectangleShape& connectedTile) : onTile(connectedTile)
{
	pos_x = 0;
	pos_y = 0;

	// TODO : work on color and radius
	c_shape.setRadius(11.f);
	c_shape.setFillColor(sf::Color{ 190, 188, 167, 150 });
	c_shape.setOrigin(sf::Vector2f{ c_shape.getPosition().x + c_shape.getGlobalBounds().getSize().x / 2 ,
		c_shape.getPosition().y + c_shape.getGlobalBounds().getSize().y / 2 });

}

sf::CircleShape& PossibleMove::getShape()
{
	return c_shape;
}

void PossibleMove::setPosition(sf::Vector2f pos_)
{
	c_shape.setPosition(pos_);
}
