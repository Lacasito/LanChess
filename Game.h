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

#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include "GraphicsEngine.h"
#include <string>

class Game {

	private:
		Board* board;
		GraphicsEngine* engine;
		LCVAR_Color turn;

		void getEvent(LCVAR_Event& event);
		void parseUserInput(LCVAR_Event& event);
		void drawPieces();
		void drawBoard();
		void refreshScreen();
		void handleErrors(short errorCode);
		void drawToScreen();
		void resetEvent(LCVAR_Event& event);

	public:
		Game(char** argv);
		~Game();

		void drawEverything();
		void run();


};

#endif /* GAME_H_ */
