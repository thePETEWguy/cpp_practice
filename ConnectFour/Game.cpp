#include "Game.h"
#include <iostream>

Game::Game(){
	initGame();
}

Game::~Game() {
}

void Game::initGame() {
	gameOver = false;
	player = 1;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			board[i][j] = '_';
		}
	}
}

void Game::printBoard() {
	system("cls");
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << "\n";
	}
}

bool Game::isColFull(int col) {
	return board[0][col] != '_';
}

bool Game::hasWonHorizontal(int row) {
	int i;
	int piece = 0;

	for (i = 0; i < 6; i++) {
		if (board[row][i] == board[row][i + 1] && board[row][i] != '_') {
			piece++;
		}
		else {
			piece = 0;
		}

		if (piece == 3)
			return true;
	}
	return false;
}

bool Game::hasWonVertical(int col) {
	int i;
	int piece = 0;

	for (i = 0; i < 6; i++) {
		if (board[i][col] == board[i + 1][col] && board[i][col] != '_') {
			piece++;
		}
		else {
			piece = 0;
		}

		if (piece == 3)
			return true;
	}
	return false;
}

bool Game::hasWonMainDiag(int row, int col) {
	int i, j;

	if (row >= col) {
		i = abs(row - col);
		j = 0;
	}
	else {
		i = 0;
		j = abs(row - col);
	}

	int piece = 0;
	while (i < 5 && j < 6) {
		if (board[i][j] == board[i + 1][j + 1] && board[i][j] != '_') {
			piece++;
		}
		else {
			piece = 0;
		}
		if (piece == 3)
			return true;
		i++;
		j++;
	}
	return false;
}

bool Game::hasWonSecDiag(int row, int col) {
	int i, j;

	if (row + col <= 5) {
		i = 0;
		j = row + col;
	}
	else {
		i = abs(6 - (col + row));
		j = 6;
	}

	int piece = 0;
	
	while (i <= 4 && j > 0) {
		if (board[i][j] == board[i + 1][j - 1] && board[i][j] != '_') {
			piece++;
		}
		else {
			piece = 0;
		}
		if (piece == 3)
			return true;
		i++;
		j--;
	}
	return false;
}

bool Game::hasWon(int row, int col) {
	if (hasWonHorizontal(row) || hasWonVertical(col) || hasWonMainDiag(row, col) || hasWonSecDiag(row, col))
		return true;
	return false;
}

void Game::getPlayerInput() {
	do {
		std::cout << "Player" << player << ", it is your turn!\n";
		std::cout << "Col: ";
		std::cin >> pCol;
		pCol--;
	} while (pCol < 0 || pCol > 6 || isColFull(pCol));

	int i;
	switch (player) {
	case 1:
		for (i = 0; board[i][pCol] == '_'; i++);
		board[i - 1][pCol] = 'X';
		break;
	case 2:
		for (i = 0; board[i][pCol] == '_'; i++);
		board[i - 1][pCol] = 'O';
		break;
	}

	gameOver = hasWon(i - 1, pCol);
	if (gameOver) {
		printBoard();
		std::cout << "Player" << player << " has won the game!" << std::endl;

		std::cout << "Rematch? (Y / N)";
		std::cin.ignore();
		char ch = getchar();

		if (ch == 'Y') {
			initGame();
			startGame();
		}
	}
	else {
		player = player % 2 + 1;
	}
}

void Game::startGame() {
	while (!gameOver) {
		printBoard();
		getPlayerInput();
	}
}
