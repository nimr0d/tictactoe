#ifndef _H_TYPES_
#define _H_TYPES_

#include <cstdint>

typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint8_t u8;
typedef int8_t i8;

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