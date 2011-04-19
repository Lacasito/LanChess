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

#include "GraphicsEngine.h"
#include "configLoader.h"
#include <iostream>
#include <sstream>

GraphicsEngine::GraphicsEngine (){

	windowTitle = "LanChess";
	screen = 0;

	pawnSrf = 0;
	rookSrf = 0;
	knightSrf = 0;
	bishopSrf = 0;
	kingSrf = 0;
	queenSrf = 0;

	pawnSrf_b = 0;
	rookSrf_b = 0;
	knightSrf_b = 0;
	bishopSrf_b = 0;
	kingSrf_b = 0;
	queenSrf_b = 0;

	squareSrfW = 0;
	squareSrfB = 0;
	board = 0;
	background = 0;

}

GraphicsEngine::~GraphicsEngine(){

	SDL_FreeSurface( pawnSrf );
	SDL_FreeSurface( rookSrf );
	SDL_FreeSurface( knightSrf );
	SDL_FreeSurface( bishopSrf );
	SDL_FreeSurface( queenSrf );
	SDL_FreeSurface( kingSrf );
	SDL_FreeSurface( board );
	SDL_FreeSurface( screen );

	SDL_Quit();

}

void GraphicsEngine::init(int BPP, int WIDTH, int HEIGHT, const std::string& path, short& errorCode) {

	//TODO: tidy up all this
	errorCode = 0;

	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		errorCode = 1;
		if(SDLNet_Init() < 0){
			errorCode = 5;
		}

	}else{
		screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
		width = WIDTH;
		height = HEIGHT;

		if (screen== 0){

			errorCode = 2;

		}else{

			SDL_WM_SetCaption(windowTitle.c_str(), 0);
			bool fileError = false;
			loadGraphicsFiles(path, fileError);

			fileError? errorCode = 3 : true;
		}
	}
}

SDL_Surface *GraphicsEngine::loadImg (const std::string& path){

	SDL_Surface* loadedImg = 0;
	SDL_Surface* optimizedImg = 0;

	loadedImg = IMG_Load(path.c_str());

	if(loadedImg != 0){

		optimizedImg = SDL_DisplayFormatAlpha (loadedImg);

		SDL_FreeSurface (loadedImg);

	}

	return optimizedImg;

}

void GraphicsEngine::drawBoard()
{
	drawBackground();
	drawSquares();

}

void GraphicsEngine::drawPiece(LCVAR_PieceType type, int x, int y)
{
	SDL_Surface* toDraw = 0;

	switch(type){

		case PAWN:
			toDraw = pawnSrf;
			break;

		case ROOK:
			toDraw = rookSrf;
			break;

		case KNIGHT:
			toDraw = knightSrf;
			break;

		case BISHOP:
			toDraw = bishopSrf;
			break;

		case KING:
			toDraw = kingSrf;
			break;

		case QUEEN:
			toDraw = queenSrf;
			break;
	}

	if (toDraw != 0){

		applySurface(toDraw, screen, x*width/8, y*height/8);
	}
}

void GraphicsEngine::loadGraphicsFiles(const std::string& path, bool& error){
	//FIXME: loadImg can be null!

	configLoader config(path);
	std::string fileName;

	config.loadData();

	config.getPawnFile(fileName);
	pawnSrf_b = loadImg (fileName);
	pawnSrf = loadImg (fileName);

	config.getRookFile(fileName);
	rookSrf_b = loadImg (fileName);
	rookSrf = loadImg (fileName);

	config.getKnightFile(fileName);
	knightSrf_b = loadImg (fileName);
	knightSrf = loadImg (fileName);

	config.getBishopFile(fileName);
	bishopSrf_b = loadImg (fileName);
	bishopSrf = loadImg (fileName);

	config.getQueenFile(fileName);
	queenSrf_b = loadImg (fileName);
	queenSrf = loadImg (fileName);

	config.getKingFile(fileName);
	kingSrf_b = loadImg (fileName);
	kingSrf = loadImg (fileName);

	config.getWSquareFile(fileName);
	squareSrfW = loadImg(fileName);

	config.getBSquareFile(fileName);
	squareSrfB = loadImg (fileName);

	config.getBackgroundFile(fileName);
	background = loadImg (fileName);

	//TODO: Check if the files were loaded correctly at this point!

	makeWhite(pawnSrf);
	makeWhite(rookSrf);
	makeWhite(knightSrf);
	makeWhite(bishopSrf);
	makeWhite(kingSrf);
	makeWhite(queenSrf);

}

void GraphicsEngine::applySurface(SDL_Surface *src, SDL_Surface *dest, int x, int y){

	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(src, 0, dest, &offset);
}

void GraphicsEngine::drawSquares()
{
	SDL_Surface* toDraw = 0;

	for(int i = 0; i < 8; ++i){

		for(int j = 0; j < 8; ++j){

			if( (i+j)%2 == 0 ){
				toDraw = squareSrfW;
			}else{
				toDraw = squareSrfB;
			}
				applySurface(toDraw, screen, j*width/8, i*height/8);
		}
	}
}

void GraphicsEngine::drawBackground()
{

	applySurface(background, screen, width/2, height/2);
}

void GraphicsEngine::drawToScreen()
{
	//applySurface(board, screen, 0, 0);
	SDL_Flip(screen);
}

void GraphicsEngine::getEvent(LCVAR_Event& event)
{
	//TODO: the user can't quit if he doesn't finish making the move

	SDL_Event sdlEvent;
	SDL_Rect mousePos, squareFrom;
	bool eventTaken = false;

	while(!eventTaken){

		SDL_WaitEvent(&sdlEvent);

		if(sdlEvent.type == SDL_QUIT){
			event.type = QUIT;
			eventTaken = true;
		}

		//Looking for a click
		if(sdlEvent.type == SDL_MOUSEBUTTONDOWN){

			event.type = PIECE_SELECT;

			mousePos.x = sdlEvent.motion.x;
			mousePos.y = sdlEvent.motion.y;
			posToSquare(mousePos, squareFrom);

			intToString(squareFrom.x, event.param[0]);
			intToString(squareFrom.y, event.param[1]);

			eventTaken = true;
		}
	}
}

void GraphicsEngine::posToSquare(SDL_Rect& pos, SDL_Rect& square){
	square.x = pos.x/(width/8);
	square.y = pos.y/(height/8);
}

void GraphicsEngine::makeWhite(SDL_Surface* source){

	SDL_LockSurface(source);

	//TODO: Implement this function

	SDL_UnlockSurface(source);

}

void GraphicsEngine::intToString(int in, std::string& out){

	std::stringstream ss;

	ss << in;
	out = ss.str();
}

bool GraphicsEngine::connectTo(const string& ip){

	return false;
}
