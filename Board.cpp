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

#include "Board.h"
#include <cstdlib>
#include <iostream>

Board::Board(LCVAR_Color color) {
	
	//TODO:if the game is in LAN, DO NOT check legal moves for other players?

	LCVAR_Color enemyColor = (color == WHITE) ? BLACK : WHITE;
	playerColor = color;

	addPiece(ROOK, color, 0, 7);
	addPiece(KNIGHT, color, 1, 7);
	addPiece(BISHOP, color, 2, 7);
	addPiece(QUEEN, color, 3, 7);
	addPiece(KING, color, 4, 7);
	addPiece(BISHOP, color, 5, 7);
	addPiece(KNIGHT, color, 6, 7);
	addPiece(ROOK, color, 7, 7);
	
	for (int i = 0; i < 8; ++i ) {
		addPiece(PAWN, color, i, 6);
	}

	addPiece(ROOK, enemyColor, 0, 0);
	addPiece(KNIGHT, enemyColor, 1, 0);
	addPiece(BISHOP, enemyColor, 2, 0);
	addPiece(QUEEN, enemyColor, 3, 0);
	addPiece(KING, enemyColor, 4, 0);
	addPiece(BISHOP, enemyColor, 5, 0);
	addPiece(KNIGHT, enemyColor, 6, 0);
	addPiece(ROOK, enemyColor, 7, 0);

	for (int i = 0; i < 8; ++i ) {
		addPiece(PAWN, enemyColor, i, 1);
	}

	int step = 2;

	for(int i = 0; i < 8; ++i){

		for(int j = 0; j < 8; ++j){

			if (step % 2 == 0){
				boardSquares[j][i].color = WHITE;
			}else{
				boardSquares[j][i].color = BLACK;
			}

			++step;
		}
		++step;
	}

}

Board::~Board(){

	for (int i = 0; i < 8; ++i){

		for(int j = 0; j < 8; ++j){

			delete boardSquares[i][j].piece;

		}
	}

}

Piece* Board::getPiece (int x, int y) const{

	return boardSquares[x][y].piece;

}

void Board::addPiece (LCVAR_PieceType pieceType, LCVAR_Color pieceColor,
                            int x, int y)
{
	//TODO:Check that there's no piece in the current square before adding a new one

	Piece* newPiece = new Piece (pieceType, pieceColor, x, y);
	
	boardSquares[x][y].piece = newPiece;

}

void Board::addPiece (Piece*& piece, int x , int y)
{
	boardSquares[x][y].piece = piece;
	
	piece = 0;
}

bool Board::movePiece (int fromX, int fromY, int toX, int toY) {

	bool valid = false;

	if ( !isEmpty(fromX, fromY) ) { //a piece exists

		if ( legalMove(fromX, fromY, toX, toY) ) {
			valid = true;

			if (!isEmpty(toX, toY)){
				delete boardSquares[toX][toY].piece;
			}
			boardSquares[toX][toY].piece = boardSquares[fromX][fromY].piece;
			boardSquares[fromX][fromY].piece = 0;

			//TODO: Do something with this
			boardSquares[toX][toY].piece->setPosition(toX, toY);
		}

	}

	return valid;
}

bool Board::isEmpty(int x, int y) const
{
	return boardSquares[x][y].piece == 0;
}

bool Board::isDiagonal(int fromX, int fromY, int toX, int toY) const
{
	return std::abs(fromX - toX) == std::abs(fromY - toY);
}

bool Board::isClearDiagonal(int fromX, int fromY, int toX, int toY) const
{
	bool clear = true;

	if (isDiagonal(fromX, fromY, toX, toY))
	{
		int step = std::abs(fromY - toY) - 1;

		int xDir = (toX - fromX) / std::abs(toX - fromX);
		int yDir = (toY - fromY) / std::abs(toY - fromY);

		//multiply by the direction to get negative/positive steps and check step iteration
		while((step != 0) && isEmpty(fromX + step*xDir, fromY + step*yDir))
		{
			--step;
		}

		if (step != 0){

			clear = false;
		}

	}else{

		clear = false;
	}

	return clear;
}

bool Board::isClearRow(int fromX, int fromY, int toX, int toY) const
{
	bool clear = true;

	if (fromY == toY){

		int step = std::abs(fromX - toX) - 1;
		int xDir = (toX - fromX) / std::abs(toX - fromX);

		while ((step != 0) && (isEmpty(fromX + step*xDir, fromY))){
			--step;
		}

		if (step != 0){

			clear = false;
		}

	}else{

		clear = false;

	}

	return clear;

}

bool Board::isClearColumn(int fromX, int fromY, int toX, int toY) const
{
	bool clear = true;

	if (fromX == toX){

		int step = std::abs(fromY - toY) - 1;
		int yDir = (toY - fromY) / std::abs(toY - fromY);

		while ((step != 0) && (isEmpty(fromX, fromY + step*yDir))){
			--step;
		}

		if (step != 0){

			clear = false;
		}

	}else{

		clear = false;

	}

	return clear;

}

bool Board::legalMove (int fromX, int fromY, int toX, int toY) const
{
	bool isLegal = false;

	/*TODO: Check if there's ambiguity within the isLegal variables and the final isLegal.
	 * Maybe it's better to check if the target square is occupied at the very end of this
	 * function or even outside it. Probably make two functions: isLegalMove and isValidMove
	 * the former checks whether it is possible to make the move regardless of the board,
	 * the latter takes into account board conditions such as occupied target squares,
	 * pinned pieces, king in check, suicide etc.
	 */

	//the piece at [fromX][fromY] must exist!
	LCVAR_PieceType type = getPiece(fromX, fromY)->getType();
	LCVAR_Color pieceColor = getPiece(fromX, fromY)->getColor();

	if((toX == fromX && toY == fromY) || (pieceColor != playerColor)){

			isLegal = false;

	}else if (type == KNIGHT){

		isLegal = ((toX == fromX -1)&&(toY == fromY - 2)) ||
				((toX == fromX - 2)&&(toY == fromY - 1)) ||
				((toX == fromX - 2)&&(toY == fromY + 1)) ||
				((toX == fromX - 1)&&(toY == fromY + 2)) ||
				((toX == fromX + 1)&&(toY == fromY + 2)) ||
				((toX == fromX + 2)&&(toY == fromY + 1)) ||
				((toX == fromX + 2)&&(toY == fromY - 1)) ||
				((toX == fromX + 1)&&(toY == fromY - 2));


	}else if(type == PAWN) {

		//TODO: This is very ugly! rewrite the clearWay variable logic

		bool pawnRow, sameColumn, /*toEnemy, */clearWay, tryCapture;

		pawnRow = (fromY == 6);
		sameColumn = (toX == fromX);
		tryCapture = ((toX == fromX + 1) || (toX == fromX - 1)) && (toY == fromY - 1);

		if(pawnRow){
			if(abs(toY - fromY) == 1){
				clearWay = toY < fromY && isEmpty(toX,toY);
			}
			else if(abs(toY - fromY) == 2){
				clearWay = toY < fromY && isEmpty(toX,toY) && isEmpty(toX,toY + 1);
			}else{
				clearWay = false;
			}
		}
		else{
			clearWay = abs(toY - fromY) == 1 && toY < fromY && isEmpty(toX,toY);
		}

		isLegal = (sameColumn && clearWay) || (tryCapture);

	}else if (type == BISHOP) {

		isLegal = isClearDiagonal(fromX, fromY, toX, toY);

	}else if (type == ROOK){

		isLegal = isClearRow(fromX, fromY, toX, toY) || isClearColumn(fromX, fromY, toX, toY);

	}else if (type == QUEEN){

		isLegal = isClearRow(fromX, fromY, toX, toY) ||
				isClearColumn(fromX, fromY, toX, toY) ||
				isClearDiagonal(fromX, fromY, toX, toY);

	}else if (type == KING){

		isLegal = (std::abs(toX - fromX) <= 1) && (std::abs(toY-fromY) <= 1);
	}

	//the target square is either empty or occupied by the enemy
	bool emptyTarget = isEmpty(toX, toY);

	//Todo: Make this more human-readable
	isLegal = isLegal && (emptyTarget ? true : (getPiece(toX, toY)->getColor() != getPiece(fromX, fromY)->getColor()));

	return isLegal;
}

LCVAR_Color Board::getSquareColor(int x, int y) const
{
	return boardSquares[x][y].color;
}

void Board::intToString(int in, std::string& out){
	std::stringstream ss;
	ss << in;
	out = ss.str();
}

bool Board::isEmpty(const std::string& x, const std::string& y) const
{
	return isEmpty(atoi(x.c_str()), atoi(y.c_str()));
}


