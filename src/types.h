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

enum Square {
	SQ_0, SQ_NB = 81, SQ_NONE = 82 
};
enum SSquare {
	SSQ_0, SSQ_NB = 9, SSQ_NONE = 10
}
enum Column {
	COL_0, COL_NB = 9, COL_NONE = 10 
};
enum Row {
	ROW_0, ROW_NB = 9, ROW_NONE = 10 
};

enum Piece {
	NONE, P0, P1, NA
};

enum GameState {
	ON, DRAW = 3
};

#define INFTY 0xfffffffLL
#define WIN 0xffffffLL

#endif