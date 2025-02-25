#pragma once

class ConnectFour {

private://private by default but good to put it out
	std::vector<std::vector<char>> board;
	int turns;
	int col;
	Piece gamePiece;

public:
	static enum Status;
	//static b/c don't need multiple of the same status and pieces

	static enum Piece;
	void setCol();
	void setPiece(Piece gamePiece);
	void setTurns(int turns);
	void incrementTurn();
	int getTurns();
	std::vector<std::vector<char>> makeBoard();
	void printBoard();
	bool canMakeMove();
	void makeMove();
	Status gameStatus();
	void play();
		//used learn c++ for enums chapter 13

	char pieceToChar();
};