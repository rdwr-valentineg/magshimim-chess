#include "Queen.h"
#include <math.h>

Queen::Queen(std::shared_ptr<Player> player, std::shared_ptr<Board> board, int row, int col) :
	Piece(player, board, 'q', row, col) {
}

bool Queen::legal(int row, int col) const {
	if (legalHelper(row, col)) return false;

	if (row != row_ && col != col_ && abs(row - row_) != abs(col - col_)) return false;

	if (!pathClear(row, col)) return false;

	return true;
}