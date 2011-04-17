/*  LanChess
    Copyright (C) 2011  Eugenio Cano-Manuel

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Game.h"
#include "CommonTypes.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstdlib>

Game::Game(char** argv){
	//Create a board and the engine to draw it
	LCVAR_Color color = WHITE;

	if (argv != 0){
		if(*argv[1] == 'b'){
			color = BLACK;
		}
	}

	//TODO:Initialize 'turn' here

	board = new Board(color);
	engine = new GraphicsEngine();
}

Game::~Game()
{
	delete board;
}

void Game::run() {

	/*TODO:The timer should be an object, Game::run should not call
	 * sdl functions directly
	 */

	LCVAR_Event gameEvent;
	gameEvent.type = NOTHING;
	int startTicks = 0;

	//TODO: Clean this up, do not hardcode
	turn = WHITE;

	bool gameEnd = false;
	short errorCode = 0;

	//TODO: Don't hardcode these settings
	engine->init(24, 600, 600, ".", errorCode);
	startTicks = SDL_GetTicks();

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

		if ((SDL_GetTicks() - startTicks) < (1000 / 30)){

			SDL_Delay( (1000/30) - (SDL_GetTicks() - startTicks));
		}

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

		int fromX = atoi (event.param[0].c_str());
		int fromY = atoi (event.param[1].c_str());
		int toX = atoi (event.param[2].c_str());
		int toY = atoi (event.param[3].c_str());

		board->movePiece(fromX, fromY, toX, toY);
	}
}
