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

#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>
using namespace std;

class configLoader{

private:
	string configFile;
	string pawnFile, rookFile, knightFile, bishopFile, kingFile, queenFile;
	string blackSquareFile, whiteSquareFile, backgroundFile;

public:
	//TODO: Implement getSquares() and getBackground()
	configLoader(const string& path);
	~configLoader();
	void loadData();
	void getPawnFile(string& filename);
	void getRookFile(string& filename);
	void getKnightFile(string& filename);
	void getBishopFile(string& filename);
	void getKingFile(string& filename);
	void getQueenFile(string& filename);
	void getBSquareFile(string& filename);
	void getWSquareFile(string& filename);
	void getBackgroundFile(string& filename);

};

#endif
