#include "position.h"

#include <cstring>
#include <iostream>

#include "base.h"

Bitboard Position::board(SSquare s) const {
	return microboards_[s];
}
Bitboard Position::macroboard() const {
	return macroboard_;
}
Piece Position::lpiece(SSquare s) const {
	return bb_get(macroboard_, s);
}
Piece Position::piece(Square s) const {
	return bb_get(microboards_[StLS[s][0]], StLS[s][1]);
}
Piece Position::piece(SSquare i, SSquare j) const {
	return bb_get(microboards_[i], j);
}
SSquare Position::do_move(Square s) {
	return do_move(StLS[s][0], StLS[s][1]);
}
SSquare Position::do_move(SSquare i, SSquare j) {
	const SSquare ret = lsForced_;
	// Place piece
	bb_set(microboards_[i], player_, j);
	// Check for microboard win
	const bool w = wbase[player_ - 1][microboards_[i]];
	++lsCount_[i];
	--free;
	if (w) {
		bb_set(macroboard_, player_, i);
		free -= SSQ_NB - lsCount_[i];
		// Check for win
		if (wbase[player_ - 1][macroboard_]) {
			state_ = GameState(player_);
		}
	} else if (lsCount_[i] >= SSQ_NB) {
		bb_set(macroboard_, NA, i);
	}
	// Check for draw
	if (free_ <= 0) {
		state_ = DRAW;
	}
	if (bb_get(macroboard_, j) == NONE) {
		lsForced_ = j;
		moves_ = lsCount_[j];
	} else {
		lsForced_ = SSQ_NONE;
		moves_ = free_;
	}
	player_ = Piece(player_ ^ 3);
	return ret;
}

void Position::undo_move(SSquare i, SSquare j, SSquare prev) {
	player_ = Piece(player_ ^ 3);
	if (bb_get(macroboard_, i) == player_) {
		free_ += SSQ_NB - lsCount_[i];
	}
	++free_;
	--lsCount_[i];
	moves_ = (prev == SSQ_NONE) ? free_ : lsCount_[prev];
	lsForced_ = prev;
	// Remove piece
	bb_clear(microboards_[i], j);
	bb_clear(macroboard_, i);
	state_ = ON;

}

i32 Position::moves() const {
	return moves_;
}

void Position::clear() {
	std::memset(microboards_, 0, SSQ_NB * 4);
	macroboard_ = 0;
	std::memset(lsCount_, 0, SSQ_NB);
	lsForced_ = SSQ_NONE;
	free_ = SQ_NB;
	moves_ = SQ_NB;
	player_ = P0;
	state_ = ON;
}

GameState Position::state() const {
	return state_;
}

Piece Position::player() const {
	return player_;
}

void Position::print() const {
	for (Square i = 0; i < 9; ++i) {
	    for (Square j = 0; j < 9; ++j) {

	        Piece p = piece(9 * i + j);
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
	Bitboards::print(macroboard_);
	for (i32 lsc : lsCount_) {
		std::cerr << lsc << "\n";
	}
	std::cerr << "Forced square " << int(lsForced_) << "\n";
	std::cerr << "Player " << player_ << "\n";
	std::cerr << "State " << state_ << "\n";
}