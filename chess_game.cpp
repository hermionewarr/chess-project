//functions for chess_game
#include "includes.h"
#include "Chess_board.h"
#include "chess_pieces.h"
#include "chess_game.h"

void chess_game::Rules() {
	{
		std::cout << "This is a representation of the board.\n" << std::endl;
		std::cout << "     A B C D E F G H" << std::endl;
		std::cout << "    -----------------" << std::endl;
		std::cout << " 8 | r n b q k b n r | 8" << std::endl;
		std::cout << " 7 | p p p p p p p p | 7" << std::endl;
		std::cout << " 6 | - - - - - - - - | 6" << std::endl;
		std::cout << " 5 | - - - - - - - - | 5" << std::endl;
		std::cout << " 4 | - - - - - - - - | 4" << std::endl;
		std::cout << " 3 | - - - - - - - - | 3" << std::endl;
		std::cout << " 2 | P P P P P P P P | 2" << std::endl;
		std::cout << " 1 | R N B Q K B N R | 1" << std::endl;
		std::cout << "    -----------------" << std::endl;
		std::cout << "     A B C D E F G H" << std::endl;
		std::cout << "\nThe white pieces are represented by capitals and the black by lowercase." << std::endl;
		std::cout << "The dashed lines are empty spaces on the board." << std::endl;
		std::cout << "The Pieces : P: Pawn, R : Rook or Castle, N : Knight, B : Bishop, Q : Queen, K : King." << std::endl;
		std::cout << "The rules of chess can be found here : https://en.wikipedia.org/wiki/Rules_of_chess\n" << std::endl;
		std::cout << "This game uses a version of algebraic notation: for example a move of a black pawn from E7 to empty square E5, would " << std::endl;
		std::cout << "be displayed as p:e7->-e5. A move to an empty is denoted as ->-, taking a piece ->T, castling ->C, pawn promotion ->Q." << std::endl;
		std::cout << "This is how the game will be displayed at the end, other than that you dont need to worry about it!" << std::endl;
		std::cout << "\nReady to play? (y/n)" << std::endl;
		std::string start_play;
		std::cin >> start_play;
		if (start_play == "n") { exit(0); }
		else if (start_play == "y") {
			std::cout << "Get ready! " << std::endl;
			return;
		}
		else {
			std::cout << "please enter y or n: ";
			std::cin.clear();
			std::cin >> start_play;
		}
	}
}