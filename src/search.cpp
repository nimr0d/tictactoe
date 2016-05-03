#include "search.h"

#include <cstring>
#include <iostream>
#include "board.h"
#include "base.h"
#include "evaluation.h"

void printfield(Piece *field) {
    for (Square i = 0; i < 9; ++i) {
        for (Square j = 0; j < 9; ++j) {
            std::cerr << field[9 * i + j] << " ";
        }
        std::cerr << "\n";
    }
}

void printlsc(u8 *lsc) {
    for (Square i = 0; i < 3; ++i) {
        for (Square j = 0; j < 3; ++j) {
            std::cerr << int(lsc[3 * i + j]) << " ";
        }
        std::cerr << "\n";
    }
}

i64 search(Square &ret, Piece *field, Bitboard macroboard, u8 *lsCount, u8 numFin, u32 depth, i64 alpha, i64 beta, Piece player, time_t max_time) {

	if (depth == 0 || numFin >= 9 || time(0) >= max_time) {

		i64 count = 0;

		count += dbase[macroboard] * 24;

		for (Square t = 0; t < 9; ++t) {
			Bitboard bb = LSquare(field, t);
			if (!wbase[0][bb] && !wbase[1][bb]) {
				count += dbase[bb];
			}
		}


		/*i64 arr[9];


		for (Square t = 0; t < 9; ++t) {
			if (bb_get(macroboard, t) <= 0) {
				Bitboard bb = LSquare(field, t);
				arr[t] = dbase[bb];
			} else if (bb_get(macroboard, t) == player) {
				arr[t] = 20;
			} else {
				arr[t] = -20;
			}
		}*/

		for (Square b = 0; b < 9; ++b) {
			if (bb_get(macroboard, b) == FR) {
				for (Square c = 0; c < 9; ++c) {
					Square s = LStS[b][c];
					if (field[s] == NONE) {
						ret = s;
					}
				}
			}
		}

		// return eval(arr);
		return count * (3 - 2 * player);
	}

	i64 bv = -INFTY;
	Square s;

	for (Square b = 0; b < 9; ++b) {
		if (bb_get(macroboard, b) == FR) {
			for (Square c = 0; c < 9; ++c) {

				Square s = LStS[b][c];
				if (field[s] == NONE) {

					field[s] = player;


					Square x1 = StLS1[s], x2 = StLS2[s];

					Square *s2 = LStS[x2];
					Square i1 = x1 / 3, j1 = x1 % 3, i2 = x2 / 3, j2 = x2 % 3;

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
				 			ret = s;
				 			field[s] = NONE;
				 			--lsCount[x2];
				 			return WIN;
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
				 	Square scrap;
				 	i64 v = -search(scrap, field, mb, lsCount, nf, depth - 1, -beta, -alpha, player == P0 ? P1 : P0, max_time);
				 	/*if (v == INFTY || v == -INFTY) {

				 		std::cerr << int(depth) << ": " << int(s % 9) << ", " << int(s / 9) << ", " << int(scrap) << ", " << v << ", " << player << "\n";
				 		
				 		std::cerr << "=========\n";
				 		printfield(field);
				 		std::cerr << "\n";
				 		printmb(mb);
				 		std::cerr << "\n";
				 		printlsc(lsCount);
				 		std::cerr << int(nf) << "\n";
				 		std::cerr << "=========\n";

				 	}*/

					field[s] = NONE;
					--lsCount[x2];

					if (v > bv) {
				 		bv = v;
				 		ret = s;
				 	}
				 	if (v > alpha) alpha = v;
				 	if (alpha >= beta) return bv;
				}
			}
		}
	}
	
	return bv;
}

Square think(Piece *field, Bitboard macroboard, u8 *lsCount, u8 numFin, Piece player, time_t max_time) {

	Square ret;
	i64 v = search(ret, field, macroboard, lsCount, numFin, 10, -INFTY, INFTY, player, max_time);
	std::cerr << "value: " << v << "\n";
	return ret;
}

