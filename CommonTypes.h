#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include "string"

enum LCVAR_PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };
enum LCVAR_Color { BLACK, WHITE };
enum LCVAR_EventType { MOVE, QUIT, NOTHING };

typedef struct {

	LCVAR_EventType type;
	int fx, fy, tx, ty;

} LCVAR_Event;

#endif 
