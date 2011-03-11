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
		SDL_Surface *squareSrf;
		SDL_Surface *board;

		SDL_Surface *loadImg (std::string& path);
		void applySurface(SDL_Surface *source, SDL_Surface *destination, int x, int y);

		//TODO: Use a #define instead?
		const std::string windowTitle = "LanChess";
	public:
		GraphicsEngine();
		~GraphicsEngine();

		//TODO: should init be the constructor? if so, how do we know if there was an error?
		void init(int BPP, int WIDTH, int HEIGHT, std::string& path, bool& errorCode);
		void drawBoard();
		void drawPiece(LCVAR_PieceType type, int x, int y);
		void loadGraphicsFiles(std::string& path);
};


#endif /* GRAPHICSENGINE_H_ */
