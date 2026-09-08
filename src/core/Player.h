#pragma once
#include <memory>

class King;

class Player {
	bool white_ = false;
	std::shared_ptr<King> king_;

public:
	Player(bool);
	bool is_white() const;
	std::shared_ptr<King> get_king();
	void set_king(std::shared_ptr<King>);
};

