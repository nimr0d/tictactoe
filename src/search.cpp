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

struct Stack {
	Square best_move;
	i64 static_eval;
};

struct EvalMove {
	Square move;
	i64 eval;
	EvalMove(Square move, i64 eval) : move(move), eval(eval) {}
	bool operator<(const EvalMove &other) const {
		return eval > other.eval;
	}
};

i64 qsearch(Position *pos, Stack *ss, i64 alpha, i64 beta) {
	const i64 player_sign = 3 - 2 * pos->player();
	const Bitboard mb = pos->macroboard();
	if (pos->moves() == 1) {
		for (SSquare b : esq[mb]) {
			if (b == SSQ_NONE) break;
			const Bitboard mib = pos->board(b);
			for (SSquare c : esq[mib]) {
				if (c == SSQ_NONE) break;
				const SSquare prev = pos->do_move(b, c);
				const GameState st = pos->state();
				if (st != ON) {
					pos->undo_move(b, c, prev);
					return st == DRAW ? 0 : player_sign * WIN;
				}
				(ss + 1)->static_eval = player_sign * eval(pos);
				const i64 val = -qsearch(pos, ss + 1, -beta, -alpha);
				pos->undo_move(b, c, prev);
				return val;
			}
		}
	}
	const i64 val = player_sign * eval(pos);
	if (val >= beta) {
		return beta;
	}
	if (val > alpha) {
		alpha = val;
	}
	std::vector<EvalMove> moves;
	// Find and static eval legal moves.
	for (SSquare b : esq[mb]) {
		if (b == SSQ_NONE) break;
		const Bitboard mib = pos->board(b);
		for (SSquare c : esq[mib]) {
			if (c == SSQ_NONE) break;
			const SSquare prev = pos->do_move(b, c);
			const GameState st = pos->state();
			if (st != ON) {
				pos->undo_move(b, c, prev);
				if (st == DRAW) {
					if (0 >= beta) {
						return beta;
					}
					if (0 > alpha) {
						ss->best_move = LStS[b][c];
						alpha = 0;
					}
				} else return player_sign * WIN;
			}
			if (pos->lpiece(b) != NONE || pos->moves() <= 1) {
				moves.emplace_back(LStS[b][c], player_sign * eval(pos));
			}
			pos->undo_move(b, c, prev);		
		}
	}
	// Go through moves from best to last, with alphabeta pruning.
	std::stable_sort(moves.begin(), moves.end());
	for (EvalMove m : moves) {
		const SSquare prev = pos->do_move(m.move);
		(ss + 1)->static_eval = m.eval;
		const i64 v = -qsearch(pos, ss + 1, -beta, -alpha);
		pos->undo_move(m.move, prev);
		if (v >= beta) {
			return beta;
		}
		if (v > alpha) {
			ss->best_move = m.move;
			alpha = v;
		}
	}
	return alpha;
}

i64 search(Position *pos, Stack *ss, u32 depth, i64 alpha, i64 beta) {
	const i64 player_sign = 3 - 2 * pos->player();
	if (depth == 0) {
		return qsearch(pos, ss, alpha, beta);
	}
	std::vector<EvalMove> moves;
	// Find and static eval legal moves.
	const Bitboard mb = pos->macroboard();
	for (SSquare b : esq[mb]) {
		if (b == SSQ_NONE) break;
		const Bitboard mib = pos->board(b);
		for (SSquare c : esq[mib]) {
			if (c == SSQ_NONE) break;
			const SSquare prev = pos->do_move(b, c);
			const GameState st = pos->state();
			if (st != ON) {
				pos->undo_move(b, c, prev);
				if (st == DRAW) {
					if (0 >= beta) {
						return beta;
					}
					if (0 > alpha) {
						ss->best_move = LStS[b][c];
						alpha = 0;
					}
				} else return player_sign * WIN;
			}
			moves.emplace_back(LStS[b][c], player_sign * eval(pos));
			pos->undo_move(b, c, prev);
		}
	}
	// Go through moves from best to last, with alphabeta pruning.
	std::stable_sort(moves.begin(), moves.end());
	for (EvalMove m : moves) {
		const SSquare prev = pos->do_move(m.move);
		(ss + 1)->static_eval = m.eval;
		const i64 v = -search(pos, ss + 1, depth - 1, -beta, -alpha);
		pos->undo_move(m.move, prev);
		if (v >= beta) {
			return beta;
		}
		if (v > alpha) {
			ss->best_move = m.move;
			alpha = v;
		}
	}
	return alpha;
}

Square think(Position *pos) {

	/*u32 depth = 9;
	if (move == 1) {
		return 40;
	} else if (time < 800) {
		depth = 6;
	} else if (time < 1500) {
		depth = 8;
	} else if (time >= 3500) {
		depth = 9;
	}*/

	// auto end_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(moveTime(pos, time, timePerMove));
	Stack stack[MAX_PLY + 2], *ss = stack + 1;
	search(pos, ss, 6, -INFTY, INFTY);
	return ss->best_move;
}

