#ifndef _TETROMINO_H_
#define _TETROMINO_H_

#include "block_type.h"

#include <array>
#include <vector>

typedef std::array<std::array<std::pair<int, int>, 4>, 4> Tetromino;
typedef std::vector<std::vector<std::pair<int, int>>> KickOffset;

extern Tetromino tetromino_I;
extern Tetromino tetromino_J;
extern Tetromino tetromino_L;
extern Tetromino tetromino_O;
extern Tetromino tetromino_S;
extern Tetromino tetromino_T;
extern Tetromino tetromino_Z;

extern KickOffset kick_offset_I;
extern KickOffset kick_offset_J;
extern KickOffset kick_offset_L;
extern KickOffset kick_offset_O;
extern KickOffset kick_offset_S;
extern KickOffset kick_offset_T;
extern KickOffset kick_offset_Z;

#endif // !_TETROMINO_H_