#include "Bishop.h"
#include <math.h>

Bishop::Bishop(std::shared_ptr<Player> player, std::shared_ptr<Board> board, int row, int col) :
	Piece(player, board, 'b', row, col) {
}

bool Bishop::legal(int row, int col) const {
	if (legalHelper(row, col)) return false;
	if (col == col_ || row == row_) {
		// can only move diagonally.
		return false;
	}
	if (abs(row - row_) != abs(col - col_)) {
		// not a true diagonal
		return false;
	}
	if (!pathClear(row, col)) return false;

	return true;
}