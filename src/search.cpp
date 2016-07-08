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

struct EvalInfo {
	Square move;
	i64 eval;
	bool operator<(const EvalInfo &other) {
		return eval >= other.eval;
	}
};

i64 search(Position *pos, u32 depth, i64 alpha, i64 beta,
           std::chrono::steady_clock::time_point end_time, bool ret) {

	if (depth == 0 || pos->state() != ON) {

		return eval(field, macroboard, lsCount) * (3 - 2 * player);

	}

	i64 bv = -INFTY;
	Square bs;

	std::vector<EvalInfo> pos;

	for (Square b = 0; b < 9; ++b) {
		if (bb_get(macroboard, b) == NONE) {
			for (Square c = 0; c < 9; ++c) {
				Square s = LStS[b][c];
				if (field[s] == NONE) {

					field[s] = player;

					Square x1 = StLS1[s], x2 = StLS2[s];

					Bitboard mb = macroboard;
					
					u8 nf = numFin;
					
					bool w = wbase[player - 1][LSquare(field, x2)];

				 	if ((++lsCount[x2]) >= 9) {
						bb_set(mb, NONE, x2);
						++nf;
					} else if (w) {
						++nf;
					}

				 	if (w) {

						bb_set(mb, player, x2);

						bool fw = wbase[player - 1][mb];

				 		if (fw) {
				 			field[s] = NONE;
				 			--lsCount[x2];
				 			bv = WIN;
				 			bs = s;
				 			goto finish;
				 		}

				 	}

				 	if (lsCount[x1] < 9 && bb_get(mb, x1) != P0 && bb_get(mb, x1) != P1) {
				 		for (Square g = 0; g < 9; ++g) {
				 			if (bb_get(mb, g) == FR) {
				 				bb_set(mb, NONE, g);
				 			}
				 		}
				 		bb_set(mb, FR, x1);

				 	} else {
				 		for (Square g = 0; g < 9; ++g) {
				 			if (bb_get(mb, g) == NONE && lsCount[g] < 9) {
				 				bb_set(mb, FR, g);
				 			}
				 		}
				 	}

				 	Position p;
				 	p.move = s;
				 	p.mb = mb;
				 	p.numFin = nf;
				 	// p.eval = (3 - 2 * player) * eval(field, mb, lsCount);

				 	pos.push_back(p);

				 	// i64 v = -search(field, mb, lsCount, nf, depth - 1, -beta, -alpha, Piece(player ^ 3), end_time, false);
					field[s] = NONE;
					--lsCount[x2];

					/*if (v > bv) {
				 		bv = v;
				 		bs = s;
				 	}
				 	if (v > alpha) alpha = v;
				 	if (alpha >= beta || std::chrono::steady_clock::now() > end_time) goto finish;*/
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
		/*if (std::chrono::steady_clock::now() > end_time) {
			std::cerr << "Error: depth " << depth << "\n";
		}*/
	}

	finish:
	if (ret) {
		std::cerr << "Value: " << bv << "\n";
		return bs;
	}
	return bv;
}

Square think(Piece *field, Bitboard macroboard, u8 *lsCount, u8 numFin, u8 numFree,
		Piece player, i64 time, i64 timePerMove, u32 move) {

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

	auto end_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(moveTime(time, timePerMove, numFree));

	return search(field, macroboard, lsCount, numFin, depth, -INFTY, INFTY, player, end_time, true);
}

