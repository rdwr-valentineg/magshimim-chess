#include "Pawn.h"
#include <math.h>
#include "Board.h"
#include "Player.h"

Pawn::Pawn(std::shared_ptr<Player> player, std::shared_ptr<Board> board, int row, int col) :
	Piece(player, board, 'p', row, col) {
}

bool Pawn::legal(int row, int col) const {
	if (legalHelper(row, col)) return false;

	auto player = player_.lock();
	auto board = board_.lock();
	if (player == nullptr || board == nullptr) return false;

	int row_delta = row - row_;
	int direction = player->is_white() ? 1 : -1;
	int start_row = player->is_white() ? 1 : 6;

	if (col != col_) {
		if (abs(col - col_) == 1 && row_delta == direction) {
			auto other_piece = board->get_piece(row, col);
			return other_piece != nullptr && other_piece->player() != player;
		}
		return false;
	}

	if (board->get_piece(row, col) != nullptr) return false;

	if (row_delta == direction) return true;

	if (row_ == start_row && row_delta == 2 * direction) {
		int mid_row = row_ + direction;
		return board->get_piece(mid_row, col) == nullptr;
	}

	return false;
}