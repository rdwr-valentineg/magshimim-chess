#pragma once
#include "Piece.h"

class Bishop : public Piece {
public: 
    Bishop(std::shared_ptr<Player>, std::shared_ptr<Board>, int, int);
    bool legal(int, int) const override;
};

