#ifndef BOARD_H
#define BOARD_H

#include "CommonTypes.h"
#include "Piece.h"

struct square {
	
	LCVAR_Color color;
	Piece*		piece;

};

class Board {

	private:
		square boardSquares[8][8];
		LCVAR_Color playerColor;

		bool	legalMove (int fromX, int fromY, int toX, int toY) const;
		bool	isEmpty(int x, int y) const;

		bool 	isDiagonal(int fromX, int fromY, int toX, int toY) const;

		//TODO: Decide whether to merge all these functions into 1 or not
		bool	isClearDiagonal(int fromX, int fromY, int toX, int toY) const;
		bool	isClearRow(int fromX, int fromY, int toX, int toY) const;
		bool	isClearColumn(int fromX, int fromY, int toX, int toY) const;

	public:
		Board (LCVAR_Color color);
		~Board ();

		Piece*	getPiece(int x, int y) const;
		void	addPiece(LCVAR_PieceType pieceType, LCVAR_Color pieceColor,
							int x, int y);
		void	addPiece(Piece*& piece, int x, int y);
		void 	movePiece(int fromX, int fromY, int toX, int toY);
		LCVAR_Color getSquareColor(int x, int y) const;

};

#endif 
