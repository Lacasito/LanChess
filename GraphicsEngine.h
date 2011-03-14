/*
 * GraphicsEngine.h
 *
 *  Created on: 08/03/2011
 *      Author: zero
 */

#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "CommonTypes.h"


class GraphicsEngine {

	private:
		int bpp, height, width;

		SDL_Surface *screen;
		SDL_Surface *pawnSrf, *rookSrf, *knightSrf, *bishopSrf, *kingSrf, *queenSrf;
		SDL_Surface *squareSrfW, *squareStfB;
		SDL_Surface *board;
		SDL_Surface *background;

		//TODO: Use a #define instead?
		std::string windowTitle;

		SDL_Surface *loadImg (const std::string& path);
		void applySurface(SDL_Surface *source, SDL_Surface *destination, int x, int y);
		void drawBackground();
		void drawSquares();

	public:
		GraphicsEngine();
		~GraphicsEngine();

		//TODO: should init be the constructor? if so, how do we know if there was an error?
		void init(int BPP, int WIDTH, int HEIGHT, const std::string& path, short& errorCode);
		void drawBoard();
		void drawPiece(LCVAR_PieceType type, int x, int y);
		void loadGraphicsFiles(const std::string& path, bool& error);
		void drawToScreen();
};


#endif /* GRAPHICSENGINE_H_ */
