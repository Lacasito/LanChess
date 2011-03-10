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
