#include "base.h"

#define msk Ob111111111111111111;

i64 wbase[262144];
i64 dbase[262144];

bool winning(u8 *arr) {	
	for (Square i = 0; i < 3; ++i) {
		if (arr[i] == P0 && arr[i + 1] == P0 && arr[i + 2] == P0) {
			return true;
		}
		if (arr[i] == P0 && arr[i + 3] == P0 && arr[i + 6] == P0) {
			return true;
		}
	}
	if (arr[0] == P0 && arr[4] == P0 && arr[8] == P0) {
		return true;
	}
	if (arr[2] == P0 && arr[4] == P0 && arr[6] == P0) {
		return true;
	}
 	return false;
}

void Base::init() {

	for (Bitboard b = 0; b < 262144; ++b) {

		i64 count = 0;

		Bitboard bc = b;

		u8 arr[9];
		for (Square i = 0; i < 9; ++i) {
			arr[i] = 3 & bc;
			if (arr[i] == 3) {
				goto loop;
			}
			bc >>= 2;
		}



		loop:

		dbase[b] = 0;
	}




	for (Bitboard b = 0; b < 262144; ++b) {

		i64 count = 0;

		Bitboard bc = b;

		u8 arr[9];
		for (Square i = 0; i < 9; ++i) {
			arr[i] = 3 & bc;
			if (arr[i] == 3) {
				goto loop;
			}
			bc >>= 2;
		}

		for (Square i = 0; i < 3; ++i) {
			i64 c = 0;
			bool s1 = false, s2 = false;

			for (Square j = 0; j < 3; ++j) {
				u8 pt = arr[3 * i + j];
				if (pt == 1) {
					++c;
					s1 = true;
				} else if (pt == 2) {
					--c;
					s2 = true;
				}
			}
			if (!s1 || !s2) {
				count += c;
			}
		}

		for (Square j = 0; j < 3; ++j) {
			i64 c = 0;
			bool s1 = false, s2 = false;

			for (Square i = 0; i < 3; ++i) {
				u8 pt = arr[3 * i + j];
				if (pt == 1) {
					++c;
					s1 = true;
				} else if (pt == 2) {
					--c;
					s2 = true;
				}
			}
			if (!s1 || !s2) {
				count += c;
			}
		}

		{
			i64 c = 0;
			bool s1 = false, s2 = false;

			for (Square d = 0; d < 3; ++d) {
				u8 pt = arr[4 * d];
				if (pt == 1) {
					++c;
					s1 = true;
				} else if (pt == 2) {
					--c;
					s2 = true;
				}
			}
			if (!s1 || !s2) {
				count += c;
			}
		}

		{
			i64 c = 0;
			bool s1 = false, s2 =false;

			for (Square d = 0; d < 3; ++d) {
				u8 pt = arr[2 * d + 2];
				if (pt == 1) {
					++c;
					s1 = true;
				} else if (pt == 2) {
					--c;
					s2 = true;
				}
			}
			if (!s1 || !s2) {
				count += c;
			}
		}

		loop: 

		wbase[b] = count;

	}

}