#ifndef PIECE_H
#define PIECE_H

#include "CommonTypes.h"

class Piece {

	private:
		LCVAR_PieceType	type;
		LCVAR_Color		color;
		
		int 			posX, posY;
		
	public:
		Piece (LCVAR_PieceType pieceType, LCVAR_Color pieceColor, int x, int y);
		~Piece ();

		LCVAR_PieceType getType () const;
		LCVAR_Color		getColor () const;
		
		void			setPosition (int x, int y);
		int				getX() const;
		int				getY() const;
};
#endif
