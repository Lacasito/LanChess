
#include "Game.h"
#include "CommonTypes.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstdlib>

Game::Game(){
//Create a board and the engine to draw it
	board = new Board(WHITE);
	engine = new GraphicsEngine();
}

Game::~Game()
{
	delete board;
}

void Game::run() {

	/*TODO: Should be library-independent (don't call SDL functions, instead
	 *make an event handler*/

	LCVAR_Event gameEvent;

	bool gameEnd = false;
	short errorCode = 0;

	SDL_Event event;

	//TODO: Don't hardcode these settings
	engine->init(16, 600, 600, ".", errorCode);

	handleErrors(errorCode);

	drawEverything();
	refreshScreen();

	while (!gameEnd){

		while (SDL_PollEvent(&event)){

			if (event.type == SDL_QUIT){
				gameEnd = true;
			}

		}

		getMove(gameEvent);
		//parseUserInput(move);

		drawEverything();
		refreshScreen();
	}

}
void Game::drawEverything() {
//Draw the board and then the pieces

	drawBoard();
	drawPieces();
}

void Game::drawBoard(){
//Call the engine to draw the board

	engine->drawBoard();
}

void Game::drawPieces(){
/*Check all squares in the board, get the type of piece if
 * there's a piece and call the engine to draw it in the
 * correct position
 */
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

void Game::handleErrors(short errorCode){
//This method should be able to handle all possible errors

	//TODO: Support all types of errors
	switch (errorCode){
		case 3:
		std::cout << "ERROR: File error" << std::endl;
	}
}

void Game::getMove(LCVAR_Event& event)
{

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
