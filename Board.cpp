#include "Board.h"
#include <cstdlib>
#include <iostream>

Board::Board(LCVAR_Color color) {
	
	//TODO:if the game is in LAN, DO NOT check legal moves for other players

	LCVAR_Color playerColor = color;

	addPiece(ROOK, color, 0, 7);
	addPiece(KNIGHT, color, 1, 7);
	addPiece(BISHOP, color, 2, 7);
	addPiece(QUEEN, color, 3, 7);
	addPiece(KING, color, 4, 7);
	addPiece(BISHOP, color, 5, 7);
	addPiece(KNIGHT, color, 6, 7);
	addPiece(ROOK, color, 7, 7);
	
	for (int i = 0; i < 8; ++i ) {
		addPiece(PAWN, playerColor, i, 6);
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

void Board::movePiece (int fromX, int fromY, int toX, int toY) {

	if ( !isEmpty(fromX, fromY) ) { //a piece exists

		if ( legalMove(fromX, fromY, toX, toY) ) {
			//the move is valid

			if (!isEmpty(toX, toY)){
				delete boardSquares[toX][toY].piece;
			}
			boardSquares[toX][toY].piece = boardSquares[fromX][fromY].piece;
			boardSquares[fromX][fromY].piece = 0;

			//TODO: Do something with this
			boardSquares[toX][toY].piece->setPosition(toX, toY);
		}

	}
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

	//the piece at [fromX][fromY] must exist!
	LCVAR_PieceType type = getPiece(fromX, fromY)->getType();

	if (type == KNIGHT){

		isLegal = ((toX == fromX -1)&&(toY == fromY - 2)) ||
				((toX == fromX - 2)&&(toY == fromY - 1)) ||
				((toX == fromX - 2)&&(toY == fromY + 1)) ||
				((toX == fromX - 1)&&(toY == fromY + 2)) ||
				((toX == fromX + 1)&&(toY == fromY + 2)) ||
				((toX == fromX + 2)&&(toY == fromY + 1)) ||
				((toX == fromX + 2)&&(toY == fromY - 1)) ||
				((toX == fromX + 1)&&(toY == fromY - 2));


	}else if(type == PAWN) {

		if (getPiece(fromX, fromY)->getColor() == playerColor){

			/*TODO: Check if there's ambiguity within the isLegal variables and the final isLegal.
			 * Maybe it's better to check if the target square is occupied at the very end of this
			 * function or even outside it. Probably make two functions: isLegalMove and isValidMove
			 * the former checks whether it is possible to make the move regardless of the board,
			 * the latter takes into account board conditions such as occupied target squares,
			 * pinned pieces, king in check, suicide etc.
			 */


			bool pawnRow, sameColumn, /*toEnemy, */clearWay, tryCapture;

			pawnRow = (fromY == 6);
			sameColumn = (toX == fromX);
			//toEnemy = (!isEmpty(toX,toY))&&(getPiece(toX,toY)->getColor() != getPiece(fromX, fromY)->getColor());
			clearWay = ((pawnRow && (toY==fromY + 2)) ? isEmpty(toX, 5) : true) && isEmpty(toX, toY);
			tryCapture = ((toX == fromX + 1) || (toX == fromX - 1)) && (toY == fromY - 1);

			isLegal = (sameColumn && clearWay) || (/*toEnemy && */tryCapture);



		}else{

			bool pawnRow, sameColumn, toEnemy, clearWay, tryCapture;

			pawnRow = (fromY == 1);
			sameColumn = (toX == fromX);
			toEnemy = (!isEmpty(toX,toY))&&(getPiece(toX,toY)->getColor() != getPiece(fromX, fromY)->getColor());
			clearWay = ((pawnRow && (toY == fromY - 2)) ? isEmpty(toX, 3) : true) && isEmpty(toX, toY);
			tryCapture = ((toX == fromX + 1) || (toX == fromX - 1)) && (toY == fromY + 1);

			isLegal = (sameColumn && clearWay) || (toEnemy && tryCapture);

		}

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


