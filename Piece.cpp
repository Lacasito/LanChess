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

#include "Piece.h"

Piece::Piece (LCVAR_PieceType pieceType, LCVAR_Color pieceColor, int x, int y) {

	type = pieceType;
	color = pieceColor;
	posX = x;
	posY = y;
}

Piece::~Piece () {}

LCVAR_PieceType Piece::getType () const { return type; }

LCVAR_Color Piece::getColor ()  const { return color; }

void Piece::setPosition (int x, int y) {

	posX = x;
	posY = y;

}

int Piece::getX () const { return posX; }

int Piece::getY () const { return posY; }
