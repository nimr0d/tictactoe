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
		u8 lsb() {
			u8 c = __builtin_ffsll(b_[0]);
			if (c == 0ULL && b_[1] != 0ULL) {
				c = __builtin_ffsll(b_[1]) + 64ULL;
			}
			return c;
		}
		//gcc only
		u8 unset_lsb() {
			u8 c = __builtin_ffsll(b_[0]);
			b_[0] &= (b_[0] - 1);
			if (c == 0 && b_[1] != 0) {
				c = __builtin_ffsll(b_[1]) + 64ULL;
				b_[1] &= (b_[1] - 1);
			}
			return c;
		}

		explicit operator bool() const { 
		    return b_[0] | b_[1]; 
		}

		void print() const;
	
	private:
		u64 b_[2];

};

extern Bitboard SquareBB[81]; // Bitboard for each square
extern Bitboard AdjacentSquaresBB[81]; // Bitboard of adjacent squares for each square
extern Bitboard ColumnBB[9];
extern Bitboard RowBB[9];
extern Bitboard BSquareBB[9];
extern Bitboard CrosshairBB[81]; // Row and column for every square
namespace Bitboards {
void init();
}
#endif
