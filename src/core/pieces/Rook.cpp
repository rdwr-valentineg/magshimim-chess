#include "Rook.h"

Rook::Rook(std::shared_ptr<Player> player, std::shared_ptr<Board> board, int row, int col) :
	Piece(player, board, 'r', row, col) {
}

bool Rook::legal(int row, int col) const {
	if (legalHelper(row, col)) return false;

	if (row != row_ && col != col_) return false;

	if (!pathClear(row, col)) return false;
	return true;
}