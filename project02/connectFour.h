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
	* setPiece
	*/
	static enum class Status;
	//static b/c don't need multiple of the same status and pieces

	static enum class Piece;
	ConnectFour();//constructor
	void setCol(int col);
	int getCol();
	void setPiece(Piece gamePiece);
	std::vector<std::vector<char>> makeBoard();
	void printBoard();
	bool canMakeMove();
	void makeMove();
	Status gameStatus();
	void play();
		//used learn c++ for enums chapter 13

	char pieceToChar();
};