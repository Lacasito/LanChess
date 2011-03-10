
#include "Game.h"
#include "CommonTypes.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstdlib>

Game::Game() {

	board = new Board(WHITE);

}

Game::~Game() {

	delete board;

}

void Game::draw() {

	for(int i = 0; i < 8; ++i){

		for(int j = 0; j < 8; ++j){

			Piece* piece = board->getPiece(j,i);

			if (piece != 0){

				LCVAR_PieceType type = piece->getType();

				switch(type){

							case PAWN:
								std::cout << "P";
								break;

							case ROOK:
								std::cout << "R";
								break;

							case KNIGHT:
								std::cout << "K";
								break;

							case BISHOP:
								std::cout << "B";
								break;

							case QUEEN:
								std::cout << "Q";
								break;

							case KING:
								std::cout << "*";
								break;

					}
			}else{
				std::cout << "_";

			}

		}
		std::cout << std::endl;

	}
}

void Game::run() {

	std::string move;

	bool gameEnd = false;

	draw();

	while (!gameEnd){

		getUserInput(move);
		parseUserInput(move);
		system("clear");
		draw();

		if(move == "done"){
			gameEnd = true;
		}
	}

}

void Game::getUserInput(std::string& input)
{
	std::cin >> input;
}
void Game::parseUserInput(const std::string& input)
{
	if (input != "done"){

		int fromX = int (input[0]) - 48;
		int fromY = int (input[1]) - 48;
		int toX = int (input[2]) - 48;
		int toY = int (input[3]) - 48;

		board->movePiece(fromX, fromY, toX, toY);
	}
}
