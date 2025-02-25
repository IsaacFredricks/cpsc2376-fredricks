#pragma once

class ConnectFour {

private://private by default but good to put it out
	std::vector<std::vector<char>> board{};
	int turns{};
	int col{};
	Piece gamePiece{};

public:
	/*functions to add :
	* printBoard()
	* makeBoard()
	* play()
	* canMakeMove()
	* makeMove()
	* getGameStatus()
	* setCol
	*/

	ConnectFour();//constructor
	void setCol();
	std::vector<std::vector<char>> makeBoard();
	void printBoard();
	bool canMakeMove();
	void makeMove();
	Status gameStatus();
	void play();
		//used learn c++ for enums chapter 13
	static enum class Status;
	//static b/c don't need multiple of the same status and pieces

	static enum class Piece;

	char pieceToChar(Piece p);
};