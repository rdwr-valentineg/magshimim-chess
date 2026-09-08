#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
	Rook(std::shared_ptr<Player>, std::shared_ptr<Board>, int, int);
	bool legal(int, int) const override;
};