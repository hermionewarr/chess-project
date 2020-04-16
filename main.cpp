//Hermione Warr - final project: Chess boardgame
#include "includes.h"
#include "chess_setup.h"

using namespace chess;
void Rules()
{
	std::cout << "This is a representation of the board.\n" << std::endl;
	std::cout << "     A B C D E F G H" << std::endl;
	std::cout << "    ________________" << std::endl;
	std::cout << " 8 | r n b q k b n r " << std::endl;
	std::cout << " 7 | p p p p p p p p " << std::endl;
	std::cout << " 6 | - - - - - - - - " << std::endl;
	std::cout << " 5 | - - - - - - - - " << std::endl;
	std::cout << " 4 | - - - - - - - - " << std::endl;
	std::cout << " 3 | - - - - - - - - " << std::endl;
	std::cout << " 2 | P P P P P P P P " << std::endl;
	std::cout << " 1 | R N B Q K B N R \n" << std::endl;
	std::cout << "\nThe white pieces are represented by capitals and the black by lowercase." << std::endl;
	std::cout << "The dashed lines are empty spaces on the board." << std::endl;
	std::cout << "The Pieces : P: Pawn, R : Rook or Castle, N : Knight, B : Bishop, Q : Queen, K : King." << std::endl;
	std::cout << "Link to the rules of chess : https://en.wikipedia.org/wiki/Rules_of_chess\n" << std::endl;
	std::cout << "This game uses long algebraic notation: for example to move a pawn from E7 to E5, enter e7-e5." << std::endl;
	std::cout << "\nReady to play? (y/n)" << std::endl;
	std::string start_play;
	std::cin >> start_play;
	if (start_play == "n") { exit(0); }
	else if (start_play == "y") { 
		std::cout << "Get ready! " << std::endl;
		return; 
	}
}
int main()
{
	//have a do while(!checkmate) loop
	std::cout << "\n\t    Chess Game" << std::endl;
	std::cout << "\t- by Hermione Warr \n" << std::endl;
	//option to see the rules
	std::string yn;
	std::cout << "would you like to see the rules of chess? (y/n)" << std::endl;
	std::cin >> yn;
	if (yn == "y" || yn == "Y" || yn =="yes") {
		Rules();
	}
	else if (yn == "n" || yn == "N" || yn == "no") {
		std::cout << "ok lets play!" << std::endl;
	}
	else {
		std::cout << "please enter y or n: " << std::endl;
		std::cin.ignore();
		std::cin.clear();
		std::cin >> yn;
	}
	board chess_game;
	chess_game.user_input();
	chess_game.display_board();
	return 0;
}