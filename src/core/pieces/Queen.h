#pragma once
#include "Piece.h"
class Queen : public Piece {
public:
    Queen(std::shared_ptr<Player>, std::shared_ptr<Board>, int, int);
    bool legal(int, int) const override;
};

