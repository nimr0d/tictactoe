#ifndef _H_POSITION_
#define _H_POSITION_

#include "board.h"
#include "types.h"

class Position {
public:
	Position() = default;
	Bitboard board(SSquare s) const;
	Bitboard macroboard() const;
	Piece lpiece(SSquare s) const;
	Piece piece(Square s) const;
	Piece piece(SSquare i, SSquare j) const;
	SSquare do_move(Square s);
	SSquare do_move(SSquare i, SSquare j);
	void undo_move(Square s, SSquare prev);
	void undo_move(SSquare i, SSquare j, SSquare prev);
	i32 moves() const;
	void clear();
	GameState state() const;
	Piece player() const;
	void print() const;
private:
	Bitboard microboards_[SSQ_NB];
	Bitboard macroboard_ = 0;
	i32 lsCount_[SSQ_NB];
	SSquare lsForced_ = SQ_NONE;
	i32 free_ = SQ_NB;
	i32 moves_ = SQ_NB;
	Piece player_ = P0;
	GameState state_ = ON;
};

#endif