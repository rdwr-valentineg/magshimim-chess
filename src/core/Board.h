#pragma once
#include "vector"
#include <memory>

constexpr int BOARD_SIZE = 8;
class Piece;
class Player;

class Board: public std::enable_shared_from_this<Board> {
	// Flat, row-major (index = row * BOARD_SIZE + col) instead of a
	// vector-of-vectors: matches the flat wire-protocol board string 1:1
	// and avoids any row/col mismatch that a nested-vector layout invites.
	std::vector<std::shared_ptr<Piece>> board_;

	static int index(int row, int col) { return row * BOARD_SIZE + col; }

public:
	Board(std::shared_ptr<Player>, std::shared_ptr<Player>);
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;
	void setup(std::shared_ptr<Player>, std::shared_ptr<Player>);

	std::shared_ptr<Piece> get_piece(int, int);
	bool set_piece(std::shared_ptr<Piece>, int, int);
	std::vector<std::shared_ptr<Piece>> get_board();

	bool move_piece(int, int, int, int);
	bool check_move(int, int, int, int);

	void print_board();
};

