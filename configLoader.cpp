#include "configLoader.h"
#include <fstream>

using namespace std;

configLoader::configLoader(string& fileName){
	configFile = fileName;
}

configLoader::~configLoader(){

}

void configLoader::loadData(){

	ifstream fileStream;
	string buffer;
	string* input;
	int counter = 0;

	fileStream.open(configFile.c_str(), ifstream::in);
	if (!fileStream.bad()){

		getline(fileStream, buffer);
		input = new string[6];

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

		delete [] input;
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
