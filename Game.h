
#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include "GraphicsEngine.h"
#include <string>

class Game {

	private:
		Board* board;
		GraphicsEngine* engine;

		void getEvent(LCVAR_Event& event);
		void parseUserInput(const std::string& input);
		void drawPieces();
		void drawBoard();
		void refreshScreen();
		void handleErrors(short errorCode);

	public:
		Game();
		~Game();

		void drawEverything();
		void run();


};

#endif /* GAME_H_ */
