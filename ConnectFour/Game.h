#pragma once

class Game
{
public:
	void printBoard();
	void startGame();
	void getPlayerInput();
	bool hasWon(int row, int col);

	Game();
	~Game();

private:
	void initGame();
	bool isColFull(int col);
	bool hasWonHorizontal(int row);
	bool hasWonVertical(int col);
	bool hasWonMainDiag(int row, int col);
	bool hasWonSecDiag(int row, int col);

	bool gameOver;
	int player;
	char board[6][7];

	int pCol;
};

