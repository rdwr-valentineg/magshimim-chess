#include "Knight.h"
#include <math.h>
#include <memory>

Knight::Knight(std::shared_ptr<Player> player, std::shared_ptr<Board> board, int row, int col) :
	Piece(player, board, 'n', row, col) {
}

bool Knight::legal(int row, int col) const {
	if (legalHelper(row, col)) return false;

	int row_delta = abs(row - row_);
	int col_delta = abs(col - col_);

	if (!((row_delta == 2 && col_delta == 1) || (row_delta == 1 && col_delta == 2))) {
		return false;
	}

	return true;
}