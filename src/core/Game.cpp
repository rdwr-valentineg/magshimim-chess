#include "Game.h"
#include "Piece.h"
#include "King.h"
#include <cctype>

Game::Game(Pipe& pipe) : pipe_{ pipe } {
	player1_ = std::make_shared<Player>(true);
	player2_ = std::make_shared<Player>(false);
	curr_player_ = player1_;

	board_ = std::make_shared<Board>(player1_, player2_);
	board_->setup(player1_, player2_);
}

bool Game::isValidMove(ResponseCode code) const {
	switch (code) {
	case ResponseCode::VALID_MOVE:
	case ResponseCode::VALID_CHESS_MOVE:
		return true;
	default:
		return false;
	}
}

std::shared_ptr<Player> Game::other_player() {
	if (curr_player_ == player1_) {
		return player2_;
	}
	else {
		return player1_;
	}
}

void Game::change_turn() {
	curr_player_ = other_player();
}

ResponseCode Game::try_move(std::string move) {
	if (move.size() < 4) {
		return ResponseCode::INVALID_OUT_OF_BOUNDS;
	}

	int srcRow = BOARD_SIZE - (move[1] - '0');
	int srcCol = move[0] - 'a';
	int dstRow = BOARD_SIZE - (move[3] - '0');
	int dstCol = move[2] - 'a';

	std::cout << "Move from: " << srcRow << ", " << srcCol << "To " << dstRow << ", " << dstCol << std::endl;

	if (srcRow < 0 || srcRow >= BOARD_SIZE ||
		srcCol < 0 || srcCol >= BOARD_SIZE ||
		dstRow < 0 || dstRow >= BOARD_SIZE ||
		dstCol < 0 || dstCol >= BOARD_SIZE) {
		return ResponseCode::INVALID_OUT_OF_BOUNDS;
	}

	auto srcPiece = board_->get_piece(srcRow, srcCol);
	if (srcPiece == nullptr || srcPiece->player() != curr_player_) return ResponseCode::INVALID_NOT_YOUR_PLAYER;

	auto dstPiece = board_->get_piece(dstRow, dstCol);
	if (dstPiece != nullptr && dstPiece->player() == curr_player_) return ResponseCode::INVALID_DEST_NOT_FREE;


	if (srcRow == dstRow && srcCol == dstCol) return ResponseCode::INVALID_SRC_AND_DEST_EQUAL;

	if (!board_->check_move(srcRow, srcCol, dstRow, dstCol)) return ResponseCode::INVALID_ILLEGAL_MOVE;

	board_->move_piece(srcRow, srcCol, dstRow, dstCol);

	// check for chess
	if (curr_player_->get_king()->chess()) {
		// illegal move (leaves/puts our own king in check) — undo it
		srcPiece->move(srcRow, srcCol);
		board_->set_piece(srcPiece, srcRow, srcCol);
		board_->set_piece(dstPiece, dstRow, dstCol);

		return ResponseCode::INVALID_CHESS_WILL_OCCURE;
	}



	ResponseCode res;
	if (other_player()->get_king()->chess()) {
		res = ResponseCode::VALID_CHESS_MOVE;
	} else {
		res = ResponseCode::VALID_MOVE;
	}

	this->change_turn();
	return res;

}

std::string Game::board_to_string() const {
	std::string result;
	result.reserve(BOARD_SIZE * BOARD_SIZE);

	for (auto& piece : board_->get_board()) {
		if (piece == nullptr) {
			result += '#';
			continue;
		}

		char sign = piece->sign();
		auto owner = piece->player();
		if (owner != nullptr && owner->is_white()) {
			sign = static_cast<char>(std::toupper(static_cast<unsigned char>(sign)));
		}
		result += sign;
	}

	return result;
}

std::string Game::initial_message() const {
	std::string message = board_to_string();
	message += curr_player_->is_white() ? '0' : '1';
	return message;
}

std::string Game::result_message(ResponseCode code) const {
	return std::string(1, static_cast<char>('0' + static_cast<int>(code)));
}