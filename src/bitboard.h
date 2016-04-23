#ifndef _H_BITBOARD_
#define _H_BITBOARD_

#include "types.h"

class Bitboard {
	public:
		Bitboard() = default;

		Bitboard(u64 b0, u64 b1) : b_{b0, b1} {}

		Bitboard operator<<(i32 shift) const {
			if (shift >= 64) {
				return Bitboard(0ULL, b_[0] << (shift - 64));
			}
			if (shift == 0) return *this;
			return Bitboard(b_[0] << shift, (b_[1] << shift) | (b_[0] >> (64 - shift)));
		}

		Bitboard operator>>(i32 shift) const {
			if (shift >= 64) {
				return Bitboard(b_[1] >> (shift - 64), 0ULL);
			}
			if (shift == 0) return *this;
			return Bitboard((b_[0] >> shift) | (b_[1] << (64 - shift)), b_[1] >> shift);
		}

		Bitboard operator&(const Bitboard& other) const {
			return Bitboard(b_[0] & other.b_[0], b_[1] & other.b_[1]);
		}

		void operator&=(const Bitboard& other) {
			b_[0] &= other.b_[0];
			b_[1] &= other.b_[1]; 
		}

		Bitboard operator|(const Bitboard& other) const {
			return Bitboard(b_[0] | other.b_[0], b_[1] | other.b_[1]);
		}

		void operator|=(const Bitboard& other) {
			b_[0] |= other.b_[0];
			b_[1] |= other.b_[1]; 
		}

		Bitboard operator^(const Bitboard& other) const {
			return Bitboard(b_[0] ^ other.b_[0], b_[1] ^ other.b_[1]);
		}

		void operator^=(const Bitboard& other) {
			b_[0] ^= other.b_[0];
			b_[1] ^= other.b_[1];
		}

		Bitboard operator~() const {
			return Bitboard(~b_[0], ~b_[1]);
		}

		bool operator==(const Bitboard& other) const {
			return (b_[0] == other.b_[0]) && (b_[1] == other.b_[1]);
		}

		bool operator!=(const Bitboard& other) const {
			return (b_[0] ^ other.b_[0]) || (b_[1] ^ other.b_[1]);
		}

		// gcc only
		Square lsb() {
			Square c = __builtin_ffsll(b_[0]);
			if (c == 0ULL && b_[1] != 0ULL) {
				c = __builtin_ffsll(b_[1]) + 64ULL;
			}
			return c;
		}

		//gcc only
		Square unset_lsb() {
			Square c = __builtin_ffsll(b_[0]);
			b_[0] &= (b_[0] - 1);
			if (c == 0 && b_[1] != 0) {
				c = __builtin_ffsll(b_[1]) + 64ULL;
				b_[1] &= (b_[1] - 1);
			}
			return c;
		}

		//gcc only
		u8 popcount() {
			return __builtin_popcountll(b_[0]) + __builtin_popcountll(b_[1]);
		}

		operator bool() const { 
		    return b_[0] | b_[1]; 
		}

		void print() const;
	
	private:
		u64 b_[2];

};

// gcc only
inline Square lsb(SBitboard bb) {
	return __builtin_ffs(bb);
}

//gcc only
inline Square unset_lsb(SBitboard &bb) {
	u8 c = __builtin_ffs(bb);
	bb &= (bb - 1);
	return c;
}

//gcc only
inline u8 popcount(SBitboard bb) {
	return __builtin_popcount(bb);
}

void print(SBitboard bb);


extern Bitboard SquareBB[81]; // Bitboard for each square
extern Bitboard AdjacentSquaresBB[81]; // Bitboard of adjacent squares for each square
extern Bitboard ColumnBB[9]; // Bitboard for each column.
extern Bitboard RowBB[9]; // Bitboard for each row.
extern Bitboard LSquareBB[9]; // Bitboard for each large square.
extern Bitboard CrosshairBB[81]; // Row and column for every square

extern SBitboard SquareSBB[9];
extern SBitboard ColumnSBB[3];
extern SBitboard RowSBB[3];
extern SBitboard DiagSBB[2];

namespace Bitboards {
void init();
}
#endif
