#include "Board.h"
#include "Player.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream> 

Board::Board(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2) {
	board_ = std::vector<std::shared_ptr<Piece>>(BOARD_SIZE * BOARD_SIZE, nullptr);
}

void Board::setup(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2) {
	auto self = shared_from_this();

	int pawn_row1 = player1->is_white() ? 1 : 6;
	int pawn_row2 = player2->is_white() ? 1 : 6;
	int back_row1 = player1->is_white() ? 0 : 7;
	int back_row2 = player2->is_white() ? 0 : 7;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		board_[index(pawn_row1, i)] = std::make_shared<Pawn>(player1, self, pawn_row1, i);
		board_[index(pawn_row2, i)] = std::make_shared<Pawn>(player2, self, pawn_row2, i);
	}
	board_[index(back_row1, 0)] = std::make_shared<Rook>(player1, self, back_row1, 0);
	board_[index(back_row1, 1)] = std::make_shared<Knight>(player1, self, back_row1, 1);
	board_[index(back_row1, 2)] = std::make_shared<Bishop>(player1, self, back_row1, 2);
	board_[index(back_row1, 3)] = std::make_shared<Queen>(player1, self, back_row1, 3);
	board_[index(back_row1, 5)] = std::make_shared<Bishop>(player1, self, back_row1, 5);
	board_[index(back_row1, 6)] = std::make_shared<Knight>(player1, self, back_row1, 6);
	board_[index(back_row1, 7)] = std::make_shared<Rook>(player1, self, back_row1, 7);

	auto king1 = std::make_shared<King>(player1, self, back_row1, 4);
	board_[index(back_row1, 4)] = king1;
	player1->set_king(king1);
	board_[index(back_row2, 0)] = std::make_shared<Rook>(player2, self, back_row2, 0);
	board_[index(back_row2, 1)] = std::make_shared<Knight>(player2, self, back_row2, 1);
	board_[index(back_row2, 2)] = std::make_shared<Bishop>(player2, self, back_row2, 2);
	board_[index(back_row2, 3)] = std::make_shared<Queen>(player2, self, back_row2, 3);
	board_[index(back_row2, 5)] = std::make_shared<Bishop>(player2, self, back_row2, 5);
	board_[index(back_row2, 6)] = std::make_shared<Knight>(player2, self, back_row2, 6);
	board_[index(back_row2, 7)] = std::make_shared<Rook>(player2, self, back_row2, 7);

	auto king2 = std::make_shared<King>(player2, self, back_row2, 4);
	board_[index(back_row2, 4)] = king2;
	player2->set_king(king2);
}

std::shared_ptr<Piece> Board::get_piece(int row, int col) {
	if (row < 0 || row > BOARD_SIZE - 1 || col < 0 || col > BOARD_SIZE - 1) return nullptr;
	return board_[index(row, col)];
}

bool Board::set_piece(std::shared_ptr<Piece> piece, int row, int col) {
	if (row < 0 || row > BOARD_SIZE - 1 || col < 0 || col > BOARD_SIZE - 1) return false;
	board_[index(row, col)] = piece;
	return true;
}
bool Board::check_move(int from_row, int from_col, int to_row, int to_col) {
	auto piece = get_piece(from_row, from_col);
	if (piece == nullptr) return false;
	if (!piece->legal(to_row, to_col)) return false;

	return true;
}

bool Board::move_piece(int from_row, int from_col, int to_row, int to_col) {
	auto piece = get_piece(from_row, from_col);
	if (piece == nullptr) return false;
	if (!piece->legal(to_row, to_col)) return false;

	board_[index(from_row, from_col)] = nullptr;
	board_[index(to_row, to_col)] = piece;
	piece->move(to_row, to_col);

	return true;
}

std::vector<std::shared_ptr<Piece>> Board::get_board() {
	return board_;
}

void Board::print_board() {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		std::cout <<"--- --- ---";
		for (int j = 0; j < BOARD_SIZE; ++j) {
			char sign = board_[index(i, j)] != nullptr ? board_[index(i, j)]->sign() : '.';
			std::cout << "|" << sign << " | ";
		}
		std::cout << std::endl;
	}
}