#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine (){

	windowTitle = "LanChess";
	screen = 0;
	pawnSrf = 0;
	rookSrf = 0;
	knightSrf = 0;
	bishopSrf = 0;
	kingSrf = 0;
	queenSrf = 0;
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

	std::string fullPath = "square.png";

	rookSrf = loadImg ("rook.png");
	knightSrf = loadImg ("knight.png");
	bishopSrf = loadImg ("bishop.png");
	queenSrf = loadImg ("queen.png");
	pawnSrf = loadImg ("pawn.png");
	kingSrf = loadImg ("king.png");
	squareSrfW = loadImg ("square_white.png");
	squareSrfB = loadImg ("square_black.png");
	background = loadImg ("back.png");

	if (squareSrfW == 0){
		error = true;
	}

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
	SDL_Rect mousePos, squareFrom, squareTo;
	bool eventTaken = false, validMove = false;

	while((!eventTaken)&&(SDL_PollEvent(&sdlEvent))){

		//Looking for a click
		if(sdlEvent.type == SDL_MOUSEBUTTONDOWN){
			mousePos.x = sdlEvent.motion.x;
			mousePos.y = sdlEvent.motion.y;
			posToSquare(mousePos, squareFrom);

			//We're looking for a second click on the destination square
			while(!validMove){
					while(SDL_PollEvent(&sdlEvent)){

							if(sdlEvent.type == SDL_MOUSEBUTTONDOWN){

									mousePos.x = sdlEvent.motion.x;
									mousePos.y = sdlEvent.motion.y;
									posToSquare(mousePos, squareTo);

									event.type = MOVE;
									event.fx = squareFrom.x;
									event.fy = squareFrom.y;
									event.tx = squareTo.x;
									event.ty = squareTo.y;

									eventTaken = true;
									validMove = true;
							}
					}
			}
		}

		if(sdlEvent.type == SDL_QUIT){
			event.type = QUIT;
			eventTaken = true;
		}
	}
}

void GraphicsEngine::posToSquare(SDL_Rect& pos, SDL_Rect& square){
	square.x = pos.x/(width/8);
	square.y = pos.y/(height/8);
}




