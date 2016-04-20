#include "bitboard.h"
#include "types.h"
#include <iostream>

int main() {
	Bitboards::init();
	SquareBB[20].print();
	std::cout << "\n";

	AdjacentSquaresBB[20].print();
	std::cout << "\n";

	ColumnBB[3].print();
	std::cout << "\n";

	RowBB[3].print();
	std::cout << "\n";

	CrosshairBB[20].print();
	std::cout << "\n";
	BSquareBB[3].print();
}