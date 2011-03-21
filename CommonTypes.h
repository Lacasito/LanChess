#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include "string"

enum LCVAR_PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };
enum LCVAR_Color { BLACK, WHITE };
enum LCVAR_EventType { MOVE };

typedef struct {

	LCVAR_EventType type;
	std::string meta;

} LCVAR_Event;

#endif 
