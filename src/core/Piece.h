#pragma once
#include <memory>

class Player;
class Board;

class Piece {
	char sign_;

public:
	Piece(std::shared_ptr<Player>, std::shared_ptr<Board>, char, int, int);
	virtual ~Piece() = default;
	virtual bool legal(int, int) const = 0;

	char sign() const;
	std::shared_ptr<Player> player() const;
	void move(int, int);

protected:
	bool legalHelper(int, int) const;
	bool pathClear(int row, int col) const;

	std::weak_ptr<Player> player_;
	std::weak_ptr<Board> board_;
	int row_;
	int col_;
};

