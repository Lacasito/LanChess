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

#include "configLoader.h"
#include <fstream>

using namespace std;

configLoader::configLoader(const string& path){
	//TODO: Do not hardcode this

	configFile = path + "/config.cfg";
}

configLoader::~configLoader(){

}

void configLoader::loadData(){

	//TODO: Make more robust

	ifstream fileStream;
	string buffer;
	string* input;
	int counter = 0;

	fileStream.open(configFile.c_str(), ifstream::in);
	if (!fileStream.bad()){

		getline(fileStream, buffer);
		input = new string[9];

		while(!fileStream.fail()){
			input[counter++] = buffer;
			getline(fileStream, buffer);
		}

		pawnFile = input[0];
		rookFile = input[1];
		knightFile = input[2];
		bishopFile = input[3];
		kingFile = input[4];
		queenFile = input[5];
		blackSquareFile = input[6];
		whiteSquareFile = input[7];
		backgroundFile = input[8];

		delete [] input;

		fileStream.close();
	}


}

void configLoader::getPawnFile(string& filename){
	filename = pawnFile;
}

void configLoader::getRookFile(string& filename){
	filename = rookFile;
}

void configLoader::getKnightFile(string& filename){
	filename = knightFile;
}

void configLoader::getBishopFile(string& filename){
	filename = bishopFile;
}

void configLoader::getKingFile(string& filename){
	filename = kingFile;
}

void configLoader::getQueenFile(string& filename){
	filename = queenFile;
}

void configLoader::getBSquareFile(string& filename){
	filename = blackSquareFile;
}
void configLoader::getWSquareFile(string& filename){
	filename = whiteSquareFile;
}
void configLoader::getBackgroundFile(string& filename){
	filename = backgroundFile;
}
