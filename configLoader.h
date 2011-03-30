#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <iostream>
#include <string>
using namespace std;

class configLoader{

private:
	string configFile;
	string pawnFile, rookFile, knightFile, bishopFile, kingFile, queenFile;

public:
	configLoader(string fileName);
	~configLoader();
	void getPawnFile(string& filename);
	void getRookFile(string& filename);
	void getKnightFile(string& filename);
	void getBishopFile(string& filename);
	void getKingFile(string& filename);
	void getQueenFile(string& filename);

};

#endif
