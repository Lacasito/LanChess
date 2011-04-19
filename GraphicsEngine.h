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

#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "CommonTypes.h"
#include "SDL/SDL_net.h"
#include "DevUtils.h"


class GraphicsEngine {
	//TODO:Use less variables (ie. Use method variables where possible)

	private:
		int bpp, height, width;

		SDL_Surface *screen;
		SDL_Surface *pawnSrf, *rookSrf, *knightSrf, *bishopSrf, *kingSrf, *queenSrf;
		SDL_Surface *pawnSrf_b, *rookSrf_b, *knightSrf_b, *bishopSrf_b, *kingSrf_b, *queenSrf_b;
		SDL_Surface *squareSrfW, *squareSrfB;
		SDL_Surface *board;
		SDL_Surface *background;

		TCPsocket socketDescriptor, serverSocket;
		IPaddress localIp, *remoteIp;

		SwissKnife utils;

		//TODO: Use a #define instead?
		std::string windowTitle;

		SDL_Surface *loadImg (const std::string& path);
		void applySurface(SDL_Surface *source, SDL_Surface *destination, int x, int y);
		void drawBackground();
		void drawSquares();
		void posToSquare(SDL_Rect& pos, SDL_Rect& square);
		void makeWhite(SDL_Surface* source);
		void intToString(int in, std::string& out);
		TCPsocket TCP_Wait_Accept_Wrapper(TCPsocket in);

	public:
		GraphicsEngine();
		~GraphicsEngine();

		//TODO: should init be the constructor? if so, how do we know if there was an error?
		void init(int BPP, int WIDTH, int HEIGHT, const std::string& path, short& errorCode);
		void drawBoard();
		void drawPiece(LCVAR_PieceType type, int x, int y);
		void loadGraphicsFiles(const std::string& path, bool& error);
		void drawToScreen();
		void getEvent(LCVAR_Event& event);
		bool connectTo(const std::string& ip);
		bool hostGame();
		void getForeignEvent(LCVAR_Event& event);
		void sendForeignEvent(const LCVAR_Event& event);
};


#endif /* GRAPHICSENGINE_H_ */
