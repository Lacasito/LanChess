#include "configLoader.h"
#include <iostream>

configLoader::configLoader(string& fileName){
	configFile = filename;
}

configLoader::~configLoader(){

}

void configLoader::loadData(){

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
