#include "position.h"

Piece Position::get_piece(Square s) {
	return bb_get(microboards_[contLS[s]], posLS[s]);
}
Piece Position::get_piece(SSquare i, SSquare j) {
	return bb_get(microboards_[i], j);
}
void Position::do_move(Square s) {
	do_move(contLS[s], posLS[s]);
}
void Position::do_move(SSquare i, SSquare j) {
	// Place piece
	bb_set(microboards_[i], player_, j);
	// Check for microboard win
	bool w = wbase[player_][microboards_[i]];
	++lsCount_[i];
	if (w) {
		bb_set(macroboard_, player_, i);
		++numFin_;
		// Check for win
		if (wbase[player_][macroboard_]) {
			state_ = player_;
		}
	} else if (lsCount_[i] >= 9) {
		bb_set(macroboard_, NA, i);
		++numFin_;
	}
	// Check for draw
	if (numFin_ >= 9) {
		state_ = DRAW;
	}
	if (bb_get(macroboard_, j) == NONE) {
		lsFree_ = j;
	} else {
		lsFree_ = SQ_NONE;
	}
	player_ ^= 3;
}

void Position::undo_move(SSquare i, SSquare j, SSquare prev) {
	// Remove piece
	bb_clear(microboards_[i], j);
	--lsCount_[i];
	state_ = ON;
	lsFree_ = prev;
	if (bb_get(macroboard_, i) != NONE) {
		bb_clear(macroboard__, i);
		--numFin_;	
	}
	player_ ^= 3;
}