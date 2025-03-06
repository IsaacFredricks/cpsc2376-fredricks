#pragma once

class ConnectFour {

public:
	//used learn c++ for enums chapter 13
	enum Status { ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW };
	//static b/c don't need multiple of the same status and pieces

	enum Piece { O, C };

	void setCol(int col);
	void setPiece(Piece gamePiece);
	void setTurns(int turns);
	void incrementTurn();
	int const getTurns();
	void makeBoard();
	void printBoard();
	bool canMakeMove();
	void makeMove();
	Status gameStatus();
	void play();
	char pieceToChar();

private://private by default but good to put it out
	std::vector<std::vector<char>> board;
	int turns;
	int col;
	Piece gamePiece;
};