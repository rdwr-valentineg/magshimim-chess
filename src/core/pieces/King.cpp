#include "King.h"
#include <math.h>
#include "Board.h"

King::King(std::shared_ptr<Player> player, std::shared_ptr<Board> board, int row, int col) :
	Piece(player, board, 'k', row, col) {
}

bool King::legal(int row, int col) const {
	if (legalHelper(row, col)) return false;
	if (abs(row - row_) > 1 || abs(col - col_) > 1) return false;
	return true;
}

bool King::chess() {
	auto board = board_.lock();
	if (board == nullptr) return false;
	auto matBoard = board->get_board();
	auto curr_player = player_.lock();

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			std::shared_ptr<Piece> currPiece = matBoard[i * BOARD_SIZE + j];
			if (currPiece == nullptr) continue;
			auto player = currPiece->player();

			if (player != NULL && player.get() != curr_player.get()) {
				if (currPiece->legal(row_, col_)) {
					return true;
				}
			}
		}
	}

	return false;
}