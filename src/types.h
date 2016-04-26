#ifndef _H_TYPES_
#define _H_TYPES_

typedef unsigned long long u64;
typedef long long i64;
typedef unsigned u32;
typedef int i32;
typedef unsigned short u16;
typedef short i16;
typedef unsigned char u8;
typedef signed char i8;

typedef u8 Square;
typedef u8 Column;
typedef u8 Row;
typedef u32 Bitboard;

enum Piece {
	NONE = 0, P0 = 1, P1 = 2, FR = -1
};

#define SQUARE_NONE 81
#define INFTY 0xfffffff
#define WIN 0xffffff

#endif