#include "board.h"

Square LStS[9][9];
Square StLS1[81];
Square StLS2[81];


void Boards::init() {
	for (Square i = 0; i < 9; ++i) {
		for (Square j = 0; j < 9; ++j) {
			LStS[i][j] =  27 * (i / 3) + 3 * (i % 3) + 9 * (j / 3) + (j % 3);
		}
	}

	for (Square i = 0; i < 81; ++i) {
		StLS1[i] = 3 * ((i / 9) % 3) + i % 3;
		StLS2[i] = 3 * (i / 27) + (i / 3) % 3;
	}
}