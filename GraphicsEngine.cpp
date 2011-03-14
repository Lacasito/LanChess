#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine (){

	windowTitle = "LanChess";

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

	loadGraphicsFiles(path);

	errorCode = 0;

	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		errorCode = 1;

	}else{
		screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);

		if (screen == 0){

			errorCode = 2;

		}else{

			SDL_WM_SetCaption(windowTitle.c_str(), 0);
		}
	}
}

SDL_Surface *GraphicsEngine::loadImg (std::string& path){

	SDL_Surface* loadedImg = 0;
	SDL_Surface* optimizedImg = 0;

	loadedImg = IMG_Load(path.c_str());

	if(loadedImg != 0){

		optimizedImg = SDL_DisplayFormat (loadedImg);

		SDL_FreeSurface (loadedImg);

	}

	return optimizedImg;

}

void GraphicsEngine::drawBoard()
{
	//FIXME: board should be initialised before used
	for(int i = 0; i < 8; ++i){

		for(int j = 0; j < 8; ++j){

				applySurface(squareSrf, board, j*width/8, i*height/8);

		}
	}

}

void GraphicsEngine::drawPiece(LCVAR_PieceType type, int x, int y)
{
	SDL_Surface* toDraw = 0;

	//FIXME: Add a default case to avoid dereferencing null pointers

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

	applySurface(board, toDraw, x*width/8, y*height/8);
}

void GraphicsEngine::loadGraphicsFiles(const std::string& path){

	/*TODO: filenames should not be hard-coded or at least not in
	 * this function
	 */
	std::string pawnFile = "pawn.png";
	std::string rookFile = "rook.png";
	std::string knightFile = "knight.png";
	std::string bishopFile = "bishop.png";
	std::string kingFile = "king.png";
	std::string queenFile = "queen.png";
	std::string squareFile = "square.png";

	//FIXME: This will not work in Windows
	std::string delimiter = "/";

	//FIXME: This is only to test

	std::string fullPath = path + delimiter + pawnFile;

	pawnSrf = loadImg (fullPath);
	rookSrf = loadImg (fullPath);
	knightSrf = loadImg (fullPath);
	bishopSrf = loadImg (fullPath);
	kingSrf = loadImg (fullPath);
	queenSrf = loadImg (fullPath);
	squareSrf = loadImg (fullPath);

}

void GraphicsEngine::applySurface(SDL_Surface *src, SDL_Surface *dest, int x, int y){

	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(src, 0, dest, &offset);
}

void GraphicsEngine::drawToScreen()
{
	applySurface(board, screen, 0, 0);
	SDL_Flip(screen);
}



