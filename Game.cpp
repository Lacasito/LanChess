
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

	LCVAR_Event gameEvent;
	gameEvent.type = NOTHING;

	bool gameEnd = false;
	short errorCode = 0;

	//TODO: Don't hardcode these settings
	engine->init(24, 600, 600, ".", errorCode);

	handleErrors(errorCode);

	drawEverything();
	refreshScreen();

	while (!gameEnd){

		getEvent(gameEvent);

		if(gameEvent.type == QUIT){

			gameEnd = true;

		}else if (gameEvent.type == MOVE){
			parseUserInput(gameEvent);
		}

		drawEverything();
		refreshScreen();
		//FIXME: Change this to a constant frame rate
		usleep(5000);
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

void Game::getEvent(LCVAR_Event& event)
{
	engine->getEvent(event);

}
void Game::parseUserInput(LCVAR_Event& event)
{
	if (event.type != QUIT){

		int fromX = event.fx;
		int fromY = event.fy;
		int toX = event.tx;
		int toY = event.ty;

		board->movePiece(fromX, fromY, toX, toY);
	}
}
