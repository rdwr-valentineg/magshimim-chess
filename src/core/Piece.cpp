#include "Piece.h"
#include "Board.h"

Piece::Piece(std::shared_ptr<Player> player, std::shared_ptr<Board> board, char sign, int row, int col) :
	sign_{ sign }, player_{ player }, board_{ board }, row_{ row }, col_{ col } {
}

char Piece::sign() const {
	return sign_;
}

std::shared_ptr<Player> Piece::player() const {
	return player_.lock();
}

void Piece::move(int row, int col) {
	col_ = col;
	row_ = row;
}

bool Piece::legalHelper(int row, int col) const {
	auto player = player_.lock();
	auto board = board_.lock();
	if (player == nullptr) return true;
	if (row == row_ && col == col_) return true;
	if (board == nullptr) return true;
	auto occupant = board->get_piece(row, col);
	if (occupant != nullptr && occupant->player() == player) return true;
	return false;
}

bool Piece::pathClear(int row, int col) const {
	auto board = board_.lock();
	if (board == nullptr) return false;

	int row_step = (row > row_) - (row < row_);
	int col_step = (col > col_) - (col < col_);
	int r = row_ + row_step;
	int c = col_ + col_step;
	while (r != row || c != col) {
		if (board->get_piece(r, c) != nullptr) return false;
		r += row_step;
		c += col_step;
	}
	return true;
}