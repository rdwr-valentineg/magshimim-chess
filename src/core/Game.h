#pragma once
#include <memory>
#include "Pipe.h"
#include "Board.h"
#include "Player.h"

enum class ResponseCode {
    VALID_MOVE = 0,
    VALID_CHESS_MOVE,
    INVALID_NOT_YOUR_PLAYER,
    INVALID_DEST_NOT_FREE,
    INVALID_CHESS_WILL_OCCURE,
    INVALID_OUT_OF_BOUNDS,
    INVALID_ILLEGAL_MOVE,
    INVALID_SRC_AND_DEST_EQUAL,
    CHECK_MATE
};

class Game {
	std::shared_ptr<Player> player1_;
	std::shared_ptr<Player> player2_;
	std::shared_ptr<Player> curr_player_;

	std::shared_ptr<Board> board_;

	Pipe pipe_;

public:
	Game(Pipe&);
	bool isValidMove(ResponseCode) const;
    std::shared_ptr<Player> other_player();
	void change_turn();

    ResponseCode try_move(std::string);

	std::string board_to_string() const;
	std::string initial_message() const;
	std::string result_message(ResponseCode) const;
};