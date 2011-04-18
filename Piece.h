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
