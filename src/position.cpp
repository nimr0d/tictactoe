#include "position.h"

#include "base.h"

#include <iostream>

Piece Position::get_board(SSquare s) const {
	return bb_get(macroboard_, s);
}
Piece Position::get_piece(Square s) const {
	return bb_get(microboards_[cntLS[s]], posLS[s]);
}
Piece Position::get_piece(SSquare i, SSquare j) const {
	return bb_get(microboards_[i], j);
}
SSquare Position::do_move(Square s) {
	return do_move(cntLS[s], posLS[s]);
}
SSquare Position::do_move(SSquare i, SSquare j) {
	const SSquare ret = lsFree_;
	// Place piece
	bb_set(microboards_[i], player_, j);
	std::cerr << microboards_[i] << "\n";
	// Check for microboard win
	const bool w = wbase[player_][microboards_[i]];
	++lsCount_[i];
	if (w) {
		bb_set(macroboard_, player_, i);
		++numFin_;
		// Check for win
		if (wbase[player_][macroboard_]) {
			state_ = GameState(player_);
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
	player_ = Piece(player_ ^ 3);
	return ret;
}

void Position::undo_move(SSquare i, SSquare j, SSquare prev) {
	// Remove piece
	bb_clear(microboards_[i], j);
	--lsCount_[i];
	state_ = ON;
	lsFree_ = prev;
	if (bb_get(macroboard_, i) != NONE) {
		bb_clear(macroboard_, i);
		--numFin_;	
	}
	player_ = Piece(player_ ^ 3);
}

GameState Position::state() const {
	return state_;
}

void Position::print() const {
	for (Square i = 0; i < 9; ++i) {
	    for (Square j = 0; j < 9; ++j) {

	        Piece p = get_piece(9 * i + j);
	        char c;
	        if (p == 0) {
	            c = '_';
	        } else if (p == 1) {
	            c = 'X';
	        } else {
	            c = 'O';
	        }
	        std::cerr << c << " ";
	        if (j % 3 == 2) {
	            std::cerr << " ";
	        }
	    }
	    if (i % 3 == 2) {
	        std::cerr << "\n";
	    }
	    std::cerr << "\n";
	}
}