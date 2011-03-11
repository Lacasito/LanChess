#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine (){

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

GraphicsEngine::init(int BPP, int WIDTH, int HEIGHT, std::string& path, bool& errorCode) {

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

	return opmizedImg;

}

void GraphicsEngine::loadGraphicsFiles(std::string& path){

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

	pawnSrf = loadImg (path + delimiter + pawnFile);
	rookSrf = loadImg (path + delimiter + pawnFile);
	knightSrf = loadImg (path + delimiter + pawnFile);
	bishopSrf = loadImg (path + delimiter + pawnFile);
	kingSrf = loadImg (path + delimiter + pawnFile);
	queenSrf = loadImg (path + delimiter + pawnFile);
	squareSrf = loadImg (path + delimiter + pawnFile);

}

void GraphicsEngine::applySurface(SDL_Surface *src, SDL_Surface *dest, int x, int y){

	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(src, 0, dest, &offset);
}

