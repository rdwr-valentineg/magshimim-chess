#include "Player.h"

Player::Player(bool white): 
	white_{white} {}

bool Player::is_white() const {
	return white_;
}

std::shared_ptr<King> Player::get_king() {
	return king_;
}

void Player::set_king(std::shared_ptr<King> king) {
	king_ = king;
}