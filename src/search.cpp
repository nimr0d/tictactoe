#include "search.h"

#include <cstring>
#include <iostream>
#include "board.h"

void printfield(Piece *field) {
    for (Square i = 0; i < 9; ++i) {
        for (Square j = 0; j < 9; ++j) {
            std::cerr << field[9 * i + j] << " ";
        }
        std::cerr << "\n";
    }
}

void printmb(Piece *mb) {
    for (Square i = 0; i < 3; ++i) {
        for (Square j = 0; j < 3; ++j) {
            std::cerr << mb[3 * i + j] << " ";
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

i64 search(Square &ret, Piece *field, const Piece *macroboard, u8 *lsCount, u8 numFin, u32 depth, i64 alpha, i64 beta, Piece player) {

	i64 par = (3 - 2 * i64(player));

	if (depth == 0 || numFin >= 9) {
		i64 count = 0;
		
		for (Square t = 0; t < 9; ++t) {
			if (macroboard[t] == player) {
				++count;
			} else if (macroboard[t] == player) {
				--count;
			}
		}
		return count * par;
	}

	i64 bv = -INFTY;
	Square s;

	for (Square b = 0; b < 9; ++b) {
		if (macroboard[b] == FR) {
			for (Square c = 0; c < 9; ++c) {

				Square s = LStS[b][c];
				if (field[s] == NONE) {

					field[s] = player;


					Square x2 = StLS2[s];
					Square i = x2 / 3, j = x2 % 3, s2 = s - x2;

					Piece mb[9];
					// std::memcpy(mb, macroboard, 9);
					for (Square f = 0; f < 9; ++f) {
						mb[f] = macroboard[f];
					}
					u8 nf = numFin;
					
					bool w = ((field[s2 + i] == player) && 
						      (field[s2 + i + 1] == player) && 
						      (field[s2 + i + 2] == player)) ||
							 ((field[s2 + j] == player) && 
						      (field[s2 + j + 3] == player) && 
						      (field[s2 + j + 6] == player)) ||
							 ((i == j) && 
							  (field[s2] == player) && 
				              (field[s2 + 4] == player) && 
							  (field[s2 + 8] == player)
							 ) || 
				 			 ((i == 3 - j) && 
				 			  (field[s2 + 2] == player) && 
				              (field[s2 + 4] == player) && 
				 			  (field[s2 + 6] == player)
				 			 );

				 	if (++lsCount[x2] >= 9) {
						mb[x2] = NONE;
					} else if (w) {
						++nf;
					}

				 	if (w) {
				 		mb[x2] = player;

				 		bool fw = ((mb[i] == player) && 
						      	  (mb[i + 1] == player) && 
						          (mb[i + 2] == player)) ||
							      ((mb[j] == player) && 
						          (mb[j + 3] == player) && 
						          (mb[j + 6] == player)) ||
							      ((i == j) && 
							      (mb[0] == player) && 
				                  (mb[4] == player) && 
							      (mb[8] == player)
							      ) || 
				 			      ((i == 3 - j) && 
				 			      (mb[2] == player) && 
				                  (mb[4] == player) && 
				 			      (mb[6] == player)
				 			      );
				 		if (fw) {
				 			ret = s;
				 			field[s] = NONE;
				 			--lsCount[x2];
				 			return WIN * par;
				 		}

				 	}

				 	Square x1 = StLS1[s];

				 	if (lsCount[x1] < 9 && mb[x1] != P0 && mb[x1] != P1) {
				 		for (Square g = 0; g < 9; ++g) {
				 			if (mb[g] == FR) {
				 				mb[g] = NONE;
				 			}
				 		}
				 		mb[x1] = FR;

				 	} else {
				 		for (Square g = 0; g < 9; ++g) {
				 			if (mb[g] == NONE && lsCount[g] < 9) {
				 				mb[g] = FR;
				 			}
				 		}
				 	}
				 	Square scrap = 90;
				 	i64 v = -search(scrap, field, mb, lsCount, nf, depth - 1, -beta, -alpha, player == P0 ? P1 : P0);
				 	if (v == WIN || v == -WIN) {std::cerr << int(depth) << ": " << int(s) << ", " << int(scrap) << ", " << v << ", " << player << "\n";}

				 	/*
				 	std::cerr << "=========\n";
				 	printfield(field);
				 	std::cerr << "\n";
				 	printmb(mb);
				 	std::cerr << "\n";
				 	printlsc(lsCount);
				 	std::cerr << int(nf) << "\n";
				 	std::cerr << "=========\n";*/

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

Square think(Piece *field, Piece *macroboard, u8 *lsCount, u8 numFin, Piece player, i64 max_time) {

	Square ret;
	i64 v = search(ret, field, macroboard, lsCount, numFin, 4, -INFTY, INFTY, player);
	std::cerr << "value: " << v << "\n";
	return ret;
}

