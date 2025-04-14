#pragma once

class ConnectFour {

public:
	//used learn c++ for enums chapter 13
	enum Status { ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW };
	//static b/c don't need multiple of the same status and pieces

	enum Piece { O, C };

	ConnectFour();
	void setPiece(Piece gamePiece);
	int getTurns() const;
	void display() const;
	bool canMakeMove(int col);
	void makeMove(int col);
	Status status();
	void play(int col);
	char pieceToChar();

private://private by default but good to put it out
	std::vector<std::vector<char>> board;
	int turns;
	Piece gamePiece;
};