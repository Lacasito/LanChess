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
		bool	isEmpty(int x, int y) const;

};

#endif 
