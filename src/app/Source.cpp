#include "Pipe.h"
#include "Game.h"
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;
using std::string;


int main()
{
	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return 0;
		}
	}

	Game game(p);

	char msgToGraphics[1024];

	// Initial handshake, sent once: 64-char board + whose turn it is.
	// The graphics app tracks the board itself from here on.
	strcpy_s(msgToGraphics, game.initial_message().c_str());
	p.sendMessageToGraphics(msgToGraphics);

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// msgFromGraphics is a move per the protocol, e.g. "e2e4" (move e2 to e4)
		ResponseCode code = game.try_move(msgFromGraphics);

		// every message from here on is just the single-digit result code
		strcpy_s(msgToGraphics, game.result_message(code).c_str());
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
	return 0;
}