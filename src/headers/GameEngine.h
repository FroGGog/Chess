
#include "GameWorld.h"
#include "EntityManager.h"

struct PossibleMove {

	unsigned pos_x, pos_y;

	sf::CircleShape c_shape;
	sf::RectangleShape& onTile;

	PossibleMove(sf::RectangleShape& connectedTile);

	//getters
	sf::CircleShape& getShape();
	//setters
	void setPosition(sf::Vector2f pos_);


};


class GameEngine {

private:

	std::shared_ptr<GameWorld> gWorld;
	std::shared_ptr<EntityManager> e_manager;
	Entity* choosedPiece;

	std::vector<std::vector<std::string>> convertedGField;
	std::vector<PossibleMove> possibleMoves;

	sf::RectangleShape mouseCollider;

	void updateMouseBox(std::shared_ptr<MainWindow> win);
	void checkChoosedPiece();
	void checkMovePiece();

	//convert gWolrd gameField vector into vector<vector<std::string>>
	void convertChessBoard();

	void calcPossMoves();
	void pawnMoves();
	void rookMoves();
	void bishopMoves();
	void queenMoves();
	void knightMoves();
	void kingMoves();

	void checkHorizontal();
	void checkVertical();
	void checkDiagonals();
	void checkKnight();
	void checkKing();


public: 

	GameEngine(std::shared_ptr<GameWorld> gWorld_, std::shared_ptr<EntityManager> e_manager_);
	~GameEngine();

	void Update(std::shared_ptr<MainWindow> win);

	void render(std::shared_ptr<MainWindow> win);

};