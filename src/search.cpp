#include "search.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <vector>

#include "base.h"
#include "board.h"
#include "evaluation.h"
#include "time_mgmt.h"

struct EvalMove {
	Square move;
	i64 eval;
	EvalMove(Square move, i64 eval) : move(move), eval(eval) {}
	bool operator<(const EvalMove &other) {
		return eval > other.eval;
	}
};

i64 qsearch(Position *pos, i64 alpha, i64 beta) {
	const i64 player_sign = 3 - 2 * pos->player();
	i64 val = player_sign * eval(pos);
	if (val >= beta) {
		return beta;
	}
	if (val > alpha) {
		alpha = val;
	}
	std::vector<EvalMove> moves;
	// Find and static eval legal moves.
	for (SSquare b = 0; b < SSQ_NB; ++b) {
		if (pos->lpiece(b) == NONE) {
			Bitboard nb = pos->board(b);
			for (SSquare c = 0; c < SSQ_NB; ++c) {
				if (
				    pos->piece(b, c) == NONE
				    && wbase[pos->player() - 1][nb | (1 << c)]
				    ) {
					SSquare prev = pos->do_move(b, c);
					if (pos->state() == (pos->player() ^ 3)) {
						pos->undo_move(prev);
						return player_sign * WIN;
					}
					EvalMove e(LStS[b][c], pos->state() == NA ? 0 : player_sign * eval(pos));
					moves.push_back(e);
					pos->undo_move(prev);
				}
			}
		}
	}
	// Go through moves from best to last, with alphabeta pruning.
	std::stable_sort(moves.begin(), moves.end());
	for (EvalMove m : moves) {
		SSquare prev = pos->do_move(m.move);
		i64 v = -qsearch(pos, -beta, -alpha);
		pos->undo_move(prev);
		if (val >= beta) {
			return beta;
		}
		if (val > alpha) {
			alpha = val;
		}
	}
	return alpha;
}

i64 search(Position *pos, u32 depth, i64 alpha, i64 beta) {
	const i64 player_sign = 3 - 2 * pos->player();
	if (depth == 0) {
		return player_sign * eval(pos);
	}
	std::vector<EvalMove> moves;
	// Find and static eval legal moves.
	for (SSquare b = 0; b < SSQ_NB; ++b) {
		if (pos->lpiece(b) == NONE) {
			for (SSquare c = 0; c < SSQ_NB; ++c) {
				if (pos->piece(b, c) == NONE) {
					SSquare prev = pos->do_move(b, c);
					if (pos->state() == (pos->player() ^ 3)) {
						pos->undo_move(prev);
						return player_sign * WIN;
					}
					EvalMove e(LStS[b][c], pos->state() == NA ? 0 : player_sign * eval(pos));
					moves.push_back(e);
					pos->undo_move(prev);
				}
			}
		}
	}
	// Go through moves from best to last, with alphabeta pruning.
	std::stable_sort(moves.begin(), moves.end());
	for (EvalMove m : moves) {
		SSquare prev = pos->do_move(m.move);
		i64 v = -search(pos, depth - 1, -beta, -alpha);
		pos->undo_move(prev);
		if (val >= beta) {
			return beta;
		}
		if (val > alpha) {
			alpha = val;
		}
	}
	return alpha;
}

	/*if (depth == 0) {
		return eval(field, macroboard, lsCount) * (3 - 2 * player);
	}

	i64 bv = -INFTY;
	Square bs;

	std::vector<EvalMove> moves;

	for (SSquare b = 0; b < SSQ_NB; ++b) {
		if (pos->get_lpiece(b) == NONE) {
			for (SSquare c = 0; c < SSQ_NB; ++c) {
				if (get_piece(b, c) == NONE) {
					SSquare prev = pos->do_move(b, c);

				 	EvalMove e;
				 	e.eval = (3 - 2 * player) * eval(field, mb, lsCount);

				 	moves.push_back(e);

				 	// i64 v = -search(field, mb, lsCount, nf, depth - 1, -beta, -alpha, Piece(player ^ 3), end_time, false);
					
					pos->undo_move(b, c, prev);

					if (v > bv) {
				 		bv = v;
				 		bs = s;
				 	}
				 	if (v > alpha) alpha = v;
				 	if (alpha >= beta || std::chrono::steady_clock::now() > end_time) goto finish;
				}
			}
		}
	}

	// std::sort(pos.begin(), pos.end());

	for (Position p : pos) {

		Square move = p.move;
		field[move] = player;
		++lsCount[StLS2[move]];
		i64 v = -search(field, p.mb, lsCount, p.numFin, depth - 1, -beta, -alpha, Piece(player ^ 3), end_time, false);
		field[move] = NONE;
		--lsCount[StLS2[move]];

		if (v > bv) {
			bv = v;
	 		bs = move;
		}
		if (v > alpha) alpha = v;
		if (alpha >= beta) goto finish;
		if (std::chrono::steady_clock::now() > end_time) {
			std::cerr << "Error: depth " << depth << "\n";
		}
	}

	finish:
	if (ret) {
		std::cerr << "Value: " << bv << "\n";
		return bs;
	}
	return bv;
}*/

Square think(Position *pos, i64 time, i64 timePerMove, u32 move) {

	u32 depth = 9;
	if (move == 1) {
		return 40;
	} else if (time < 800) {
		depth = 6;
	} else if (time < 1500) {
		depth = 8;
	} else if (time >= 3500) {
		depth = 9;
	}

	auto end_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(moveTime(pos, time, timePerMove));

	return search(pos, depth, -INFTY, INFTY);
}

