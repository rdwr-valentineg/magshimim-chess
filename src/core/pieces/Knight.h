#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(std::shared_ptr<Player>, std::shared_ptr<Board>, int, int);
    bool legal(int, int) const override;
};