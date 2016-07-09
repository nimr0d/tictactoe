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


typedef u32 Bitboard;

typedef u32 Square;
typedef u8 SSquare;
typedef u8 Column;
typedef u8 Row;

#define SQ_NB 81
#define SQ_NONE 82
#define SSQ_NB 9
#define SSQ_NONE 10
#define COL_NB 9
#define COL_NONE 10
#define ROW_NB 9
#define ROW_NONE 10

enum Piece {
	NONE, P0, P1, NA
};

enum GameState {
	ON, DRAW = 3
};

#define INFTY 0xfffffffLL
#define WIN 0xffffffLL

#endif