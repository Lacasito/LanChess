
#include "Game.h"
#include "CommonTypes.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstdlib>

Game::Game() {

	engine = new GraphicsEngine();
	board = new Board(WHITE);

}

Game::~Game() {

	delete board;

}

void Game::drawEverything() {

	drawBoard();

	drawPieces();
}

void Game::drawBoard(){

	engine->drawBoard();
}

void Game::drawPieces()
{
	for(int i = 0; i < 8; ++i){

		for(int j = 0; j < 8; ++j){

			Piece* piece = board->getPiece(j,i);

			if (piece != 0){

				LCVAR_PieceType type = piece->getType();

				engine->drawPiece(type, j, i);
			}
		}
	}
}

void Game::refreshScreen()
{
	engine->drawToScreen();
}

void Game::handleErrors(short  errorCode)
{
	switch (errorCode){
		case 3:
		std::cout << "ERROR: File error" << std::endl;
	}
}

void Game::run() {

	std::string move;

	bool gameEnd = false;
	short errorCode = 0;

	//TODO: Don't hardcode these settings
	//TODO: Support all types of errors
	engine->init(16, 600, 600, ".", errorCode);

	switch (errorCode){
		case 3:
		std::cout << "ERROR: File error" << std::endl;
	}

	drawEverything();
	refreshScreen();

	while (!gameEnd){

		getUserInput(move);
		parseUserInput(move);

		drawEverything();
		refreshScreen();

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
