#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include "includes.h"
#include "Chess_board.h"
#include "chess_pieces.h"

namespace Chess_game {
	class Game {
	public:
		void Rules();
		void starting_display();
		void checkmate_display();
	};

}

#endif // !CHESS_GAME_H
