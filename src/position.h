#ifndef _H_POSITION_
#define _H_POSITION_

#include "board.h"
#include "types.h"

class Position {
public:
	Position() = default;
	Piece get_board(SSquare s) {
	Piece get_piece(Square s);
	Piece get_piece(SSquare i, SSquare j);
	SSquare do_move(Square s);
	SSquare do_move(SSquare i, SSquare j);
	void undo_move(SSquare i, SSquare j, SSquare prev);
	GameState state();
private:
	Bitboard microboards_[SSQ_NB];
	Bitboard macroboard_;
	u8 lsCount_[SSQ_NB];
	u8 numFin_;
	SSquare lsFree;
	Piece player_;
	GameState state_;
};

#endif