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
		if (*argv[2] == 's'){
			netMode = SERVER;
		}else if (*argv[2] == 'c'){
			netMode = CLIENT;
		}else if (*argv[2] == 'l'){
			netMode = LOCAL;
		}

	}

	board = new Board(color);
	engine = new GraphicsEngine();
}

Game::~Game()
{
	delete board;
}

void Game::run()
{

	LCVAR_Event gameEvent;
	gameEvent.type = NOTHING;

	bool gameEnd = false;
	short errorCode = 0;

	//TODO: Don't hardcode these settings
	engine->init(32, 600, 600, ".", errorCode);

	handleErrors(errorCode);

	drawToScreen();

	//TODO:Move this function to a more suitable place
	establishConnection("localhost");

	while (!gameEnd){

		getEvent(gameEvent);

		if(gameEvent.type == QUIT){

			gameEnd = true;

		}

		parseUserInput(gameEvent);

		drawToScreen();

		resetEvent(gameEvent);

	}

}
void Game::drawEverything()
{
//Draw the board and then the pieces

	drawBoard();
	drawPieces();
}

void Game::drawBoard()
{
//Call the engine to draw the board

	engine->drawBoard();
}

void Game::drawPieces()
{
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

void Game::handleErrors(short errorCode)
{
//This method should be able to handle all possible errors

	//TODO: Support all types of errors
	switch (errorCode){
		case 3:
			std::cout << "ERROR: File error" << std::endl;
		break;

		case 5:
			std::cout << "ERROR: Network init error" << std::endl;
		break;

		case 2:
			std::cout << "ERROR: Screen error" << std::endl;

		default:
			if (errorCode > 0){
				std::cout << "ERROR: Unknown error" << std::endl;
			}
	}
}

void Game::getEvent(LCVAR_Event& event)
{
	LCVAR_Event dummyEvent;
	dummyEvent.type = NOTHING;

	engine->getEvent(event);

	if ((event.type == PIECE_SELECT)&&(!board->isEmpty(event.param[0], event.param[1]))){

		engine->getEvent(dummyEvent);

		if (dummyEvent.type == PIECE_SELECT){
			event.param[2] = dummyEvent.param[0];
			event.param[3] = dummyEvent.param[1];

			event.type = MOVE;

		}else if (dummyEvent.type == QUIT){
			event.type = QUIT;
		}

	}else if(event.type == PIECE_SELECT){ //Means we clicked over an empty square.
		event.type = NOTHING;
	}

}
void Game::parseUserInput(LCVAR_Event& event)
{//Process user input

	if (event.type == MOVE){

		int fromX = atoi (event.param[0].c_str());
		int fromY = atoi (event.param[1].c_str());
		int toX = atoi (event.param[2].c_str());
		int toY = atoi (event.param[3].c_str());

		board->movePiece(fromX, fromY, toX, toY);
	}
}

void Game::drawToScreen()
{

	drawEverything();
	refreshScreen();

}

void Game::resetEvent(LCVAR_Event& event)
{
	//Resets the state of the event for it to be usable for the next iteration
	//of the main loop.

	event.type = NOTHING;
}

bool Game::establishConnection(const std::string& ip)
{
	bool res = false;
	
	if(netMode == SERVER){
		res = engine->hostGame();
	}else{
		res = engine->connectTo(ip);
	}

	return res;
}
