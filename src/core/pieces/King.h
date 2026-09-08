#pragma once
#include "Piece.h"

class King : public Piece {
public:
    King(std::shared_ptr<Player>, std::shared_ptr<Board>, int, int);
    bool legal(int, int) const override;
    bool chess();
};