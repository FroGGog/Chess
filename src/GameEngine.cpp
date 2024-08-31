#include "headers/GameEngine.h"

GameEngine::GameEngine(std::shared_ptr<GameWorld> gWorld_, std::shared_ptr<EntityManager> e_manager_)
{
	gWorld = gWorld_;
	e_manager = e_manager_;

	choosedPiece = nullptr;

	mouseCollider.setSize(sf::Vector2f{ 1.f,1.f });
	mouseCollider.setFillColor(sf::Color::Red);

	convertedGField = {
		{"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
		{"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
		{"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
		{"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
		{"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
		{"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
		{"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
		{"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
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

	//check if player clicked on tile and want's to move piece
	for (auto iter{ possibleMoves.begin() }; iter < possibleMoves.end(); iter++) {
		if (mouseCollider.getGlobalBounds().intersects(iter->onTile.getGlobalBounds())) {
			// minus offset of board divided by cell size
			convertedGField[choosedPiece->getPos().x][choosedPiece->getPos().y] = "   ";
			choosedPiece->setPosition((iter->onTile.getPosition().y - 32) / 64, (iter->onTile.getPosition().x - 64) / 64);
			choosedPiece->setFirstTurn();
			choosedPiece->setClicked(false);
			choosedPiece = nullptr;
			possibleMoves.clear();

			convertChessBoard();

			break;
		}
	}

}

void GameEngine::convertChessBoard()
{

	for (auto iter{ e_manager->getEntities().begin() }; iter < e_manager->getEntities().end(); iter++) {

		convertedGField[iter->getPos().x][iter->getPos().y] = iter->getStringType();

	}

	std::cout << '\n';
	for (auto& i : convertedGField) {
		for (auto& j : i) {
			std::cout << j;
		}
		std::cout << "\n";
	}

}

void GameEngine::addPossibleMove(int x, int y)
{
	sf::Vector2f pos;
	sf::Vector2f size;

	// get these to center circles
	pos = gWorld->getGField()[x][y].getPosition();
	size = gWorld->getGField()[x][y].getLocalBounds().getSize();

	// possible move has link to tile on which it is
	PossibleMove temp{ gWorld->getGField()[x][y] };

	temp.setPosition(sf::Vector2f{ pos.x + size.x / 2, pos.y + size.y / 2 });
	possibleMoves.push_back(temp);

}

bool GameEngine::checkPossibleMove(int x, int y)
{
	std::string enemyString{ " " };
	std::string friendString{ " " };

	if (choosedPiece->getColor()) {
		enemyString = "B";
		friendString = "W";
	}
	else {
		enemyString = "W";
		friendString = "B";
	}

	// if friendly piece found return true
	if (convertedGField[x][y].find(friendString) != std::string::npos) {
		return true;
	}

	if (convertedGField[x][y].find(enemyString) != std::string::npos) {

		addPossibleMove(x, y);

		return true;

	}

	return false;
}

void GameEngine::calcPossMoves()
{
	switch (choosedPiece->getType())
	{
	case FigureType::PAWN:
		pawnMoves();
		break;
	case FigureType::KNIGHT:
		knightMoves();
		break;
	case FigureType::BISHOP:
		bishopMoves();
		break;
	case FigureType::ROOK:
		rookMoves();
		break;
	case FigureType::QUEEN:
		queenMoves();
		break;
	case FigureType::KING:
		kingMoves();
		break;
	default:
		break;
	}


}

// TODO : work on PossibleMove it's shit to implement them every time like that

void GameEngine::pawnMoves()
{


	// if white pawn convert to oposite dir
	int converter = choosedPiece->getColor() ? -1 : 1;
	int maxMove = choosedPiece->getFirstTurn() ? 2 : 1;

	for (int i{ 1 }; i <= maxMove; i++) {
		if (convertedGField[choosedPiece->getPos().x + i * converter][choosedPiece->getPos().y] == "   ") {
		
			addPossibleMove(choosedPiece->getPos().x + i * converter, choosedPiece->getPos().y);
		}
		else {
			
			//make special for pawn
			/*if (checkPossibleMove(choosedPiece->getPos().x + i * converter, choosedPiece->getPos().y)) {
				break;
			}*/
		}
	}


}

void GameEngine::rookMoves()
{
	checkHorizontal();
	checkVertical();

}

void GameEngine::bishopMoves()
{
	checkDiagonals();
}

void GameEngine::queenMoves()
{
	checkHorizontal();
	checkVertical();
	checkDiagonals();
}

void GameEngine::knightMoves()
{
	checkKnight();
}

void GameEngine::kingMoves()
{
	checkKing();
}

// TODO : fix bug with pieces on right side of board can go throught pieces
void GameEngine::checkHorizontal()
{
	sf::Vector2f pos;
	sf::Vector2f size;

	//check right side
	for (int i{ 1 }; i < 8; i++) {
		if (choosedPiece->getPos().y + i > 7) {
			break;
		}
		else if (choosedPiece->getPos().y == 7) {
			break;
		}

		if (convertedGField[choosedPiece->getPos().x][choosedPiece->getPos().y + i] == "   ") {

			addPossibleMove(choosedPiece->getPos().x, choosedPiece->getPos().y + i);

		}
		else {

			if (checkPossibleMove(choosedPiece->getPos().x, choosedPiece->getPos().y + i)) {
				break;
			}

		}
	}

	for (int i{ 1 }; i < 8; i++) {
		std::cout << choosedPiece->getPos().y - i << '\n';
		if (choosedPiece->getPos().y - i < 0) {
			break;
		}
		else if (choosedPiece->getPos().y == 0) {
			break;
		}

		if (convertedGField[choosedPiece->getPos().x][choosedPiece->getPos().y - i] == "   ") {

			addPossibleMove(choosedPiece->getPos().x, choosedPiece->getPos().y - i);

		}
		else {

			if (checkPossibleMove(choosedPiece->getPos().x, choosedPiece->getPos().y - i)) {
				break;
			}
		}
	}

}

void GameEngine::checkVertical()
{
	sf::Vector2f pos;
	sf::Vector2f size;

	//check down
	for (int i{ 1 }; i < 8; i++) {
		if (choosedPiece->getPos().x + i > 7) {
			break;
		}
		else if (choosedPiece->getPos().x == 7) {
			break;
		}

		if (convertedGField[choosedPiece->getPos().x + i][choosedPiece->getPos().y] == "   ") {

			addPossibleMove(choosedPiece->getPos().x + i, choosedPiece->getPos().y);

		}
		else {

			if (checkPossibleMove(choosedPiece->getPos().x + i, choosedPiece->getPos().y)) {
				break;
			}
		}
	}

	for (int i{ 1 }; i < 8; i++) {
		if (choosedPiece->getPos().x - i < 0) {
			break;
		}
		else if (choosedPiece->getPos().x == 0) {
			break;
		}

		if (convertedGField[choosedPiece->getPos().x - i][choosedPiece->getPos().y] == "   ") {

			addPossibleMove(choosedPiece->getPos().x - i, choosedPiece->getPos().y);

		}
		else {
			if (checkPossibleMove(choosedPiece->getPos().x - i, choosedPiece->getPos().y)) {
				break;
			}
		}
	}

}

void GameEngine::checkDiagonals()
{
	sf::Vector2f pos;
	sf::Vector2f size;

	int minus = 1;

	//check up and down
	for (int repeat{ 1 }; repeat <= 4; repeat++) {

		for (int i{ 1 }; i < 8; i++) {

			//if piece on left side of board
			if (choosedPiece->getPos().x == 0) {
				break;
			}

			if (choosedPiece->getPos().x - i < 0) {
				break;
			}
			//check if piece is on top
			if (choosedPiece->getPos().y - (i * minus) < 0 || choosedPiece->getPos().y - (i * minus) > 7) {
				break;
			}

			if (convertedGField[choosedPiece->getPos().x - i][choosedPiece->getPos().y - (i * minus)] == "   ") {

				addPossibleMove(choosedPiece->getPos().x - i, choosedPiece->getPos().y - (i * minus));
			}
			else {

				if (checkPossibleMove(choosedPiece->getPos().x - i, choosedPiece->getPos().y - (i * minus))) {
					break;
				}
			}
		}
		minus = -minus;

	}

	//check down
	for (int repeat{ 1 }; repeat <= 2; repeat++) {
		for (int i{ 1 }; i < 8; i++) {

			//if piece on left side of board
			if (choosedPiece->getPos().x == 7) {
				break;
			}

			if (choosedPiece->getPos().x + i > 7) {
				break;
			}
			//check if piece is on top
			if (choosedPiece->getPos().y - (i * minus) < 0 || choosedPiece->getPos().y - (i * minus) > 7) {
				break;
			}

			if (convertedGField[choosedPiece->getPos().x + i][choosedPiece->getPos().y - (i * minus)] == "   ") {

				addPossibleMove(choosedPiece->getPos().x + i, choosedPiece->getPos().y - (i * minus));
			}
			// if enemy piece is king - check
			else {
				if (checkPossibleMove(choosedPiece->getPos().x + i, choosedPiece->getPos().y - (i * minus))) {
					break;
				}
			}
		}
		minus = -minus;

	}
}

// TODO : fix knight bug 
void GameEngine::checkKnight()
{
	sf::Vector2f pos;
	sf::Vector2f size;

	int minus = 1;

	int upDown = 2;
	int leftRight = 1;

	//check up
	for (int i{ 4 }; i >= 1; i--) {

		//go down by one square
		if (i == 2) {
			upDown--;
			leftRight++;
		}


		//if piece is on top not need to check upper
		if (choosedPiece->getPos().x == 0) {
			break;
		}

		if (choosedPiece->getPos().x - upDown < 0) {
			std::cout << i << '\n';
			minus = -minus;
			continue;
		}

		//check if some moves out of board
		if (choosedPiece->getPos().y + leftRight * minus < 0) {
			minus = -minus;
			continue;
		}
		if (choosedPiece->getPos().y + leftRight * minus > 7) {
			minus = -minus;
			continue;
		}

 		if (convertedGField[choosedPiece->getPos().x - upDown][choosedPiece->getPos().y + (leftRight * minus)] == "   ") {

			addPossibleMove(choosedPiece->getPos().x - upDown, choosedPiece->getPos().y + (leftRight * minus));

			minus = -minus;
		}
		//check if king attacked
		else {

			if (checkPossibleMove(choosedPiece->getPos().x - upDown, choosedPiece->getPos().y + (leftRight * minus))) {
				minus = -minus;
				continue;
			}
			minus = -minus;
			
		}
		

	}

	upDown = 2;
	leftRight = 1;

	//check down
	for (int i{ 4 }; i >= 1; i--) {

		//go down by one square
		if (i == 2) {
			upDown--;
			leftRight++;
		}

		// if piece is on bottom no need to check more
		if (choosedPiece->getPos().x == 7) {
			break;
		}

		if (choosedPiece->getPos().x + upDown > 7) {
			minus = -minus;
			continue;
		}
		

		//check if some moves out of board
		if (choosedPiece->getPos().y + leftRight * minus < 0) {
			minus = -minus;
			continue;
		}
		if (choosedPiece->getPos().y + leftRight * minus > 7) {
			minus = -minus;
			continue;
		}


		if (convertedGField[choosedPiece->getPos().x + upDown][choosedPiece->getPos().y + (leftRight * minus)] == "   ") {

			addPossibleMove(choosedPiece->getPos().x + upDown, choosedPiece->getPos().y + (leftRight * minus));

			minus = -minus;
		}
		//check if king attacked
		else {
			
			if (checkPossibleMove(choosedPiece->getPos().x + upDown, choosedPiece->getPos().y + (leftRight * minus))) {
				minus = -minus;
				continue;
			}
			minus = -minus;
		}

	}

}

void GameEngine::checkKing()
{
	sf::Vector2f pos;
	sf::Vector2f size;

	for (int x{ -1 }; x <= 1; x++) {
		for (int y{ -1 }; y <= 1; y++) {
			
			if (choosedPiece->getPos().x + x < 0 || choosedPiece->getPos().x + x > 7) {
				break;
			}

			if (choosedPiece->getPos().y + y < 0 || choosedPiece->getPos().y + y > 7) {
				break;
			}

			if (convertedGField[choosedPiece->getPos().x + x][choosedPiece->getPos().y + y] == "   ") {

				addPossibleMove(choosedPiece->getPos().x + x, choosedPiece->getPos().y + y);
			}
			else {
				if (checkPossibleMove(choosedPiece->getPos().x + x, choosedPiece->getPos().y + y)) {
					break;
				}
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
