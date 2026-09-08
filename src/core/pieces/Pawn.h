#pragma once
#include "Piece.h"

class Pawn: public Piece {
public:
    Pawn(std::shared_ptr<Player>, std::shared_ptr<Board>, int, int);
    bool legal(int, int) const override;
};

