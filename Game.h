
#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include <string>

class Game {

	private:
		Board* board;

		void getUserInput(std::string& input);
		void parseUserInput(const std::string& input);

	public:
		Game();
		~Game();

		void draw();
		void run();


};

#endif /* GAME_H_ */
