//this is where the funtions are defined
#include "includes.h"
#include "chess_setup.h"

using namespace chess;

//piece functions
/*std::string queen::location() {
	//iterate through the board until you find it
	//then output it and turn it into chess rank and file notation
	//std::string q_location = "d1";
	return "q_location";
}*/
std::string piece::icon() { 
	std::string icon ="-"; 
	return icon;
}
std::string queen::icon() { return piece_icon; }
std::string king::icon() { return piece_icon; }
std::string bishop::icon() { return piece_icon; }
std::string knight::icon() { return piece_icon; }
std::string rook::icon() { return piece_icon; }
std::string pawn::icon() { return piece_icon; }
std::string empty::icon() { return piece_icon; }
/*std::string queen::piece_icon() {
	if (colour == 0) {
		std::string icon = "Q";
		return icon;
	}
	else {
		std::string icon = "q";
		return icon;
	}
}*/
//board functions
void board::update_board(std::string move) {
	//checked move is put in here and current_board is updated
}
void board::display_board() {
	std::cout << "     A  B  C  D  E  F  G  H " << std::endl;
	std::cout << "    ________________________" << std::endl;
	for (int irow{}; irow < 8; irow++) {
		std::cout << " " << 8 - irow << " | ";
		for (int jcol{}; jcol < 8; jcol++) {
			std::cout << current_board.at(irow).at(jcol)->icon()<< "  ";
		}
		std::cout << std::endl;
	}
}
void board::user_input() {
	std::string option;
	std::cout << "Options:  move<M>  new game<N>  Quit<Q>  Show last move<S>" << std::endl;
	std::cin >> option;
	if (option == "m" || option == "M") {
		//ask them what they want to move and where
		//move check function call of piece
		//put into update board
	}
	else if (option == "n" || option == "N") {
		//reset
		new board();
	}
	else if (option == "q" || option == "Q") {
		std::string quit;
		std::cout << "Are you sure? (y/n)" << std::endl;
		std::cin >> quit;
		do {
			std::cout << "Pease enter y or n" << std::endl;
			std::cin >> quit;
		} while (quit != "y" || quit != "yes" || quit != "n" || quit != "no");
		
		if (quit == "y" || quit == "yes") {
			//quit game
		}
		else if (quit == "n" || quit == "N") {
			return;
		}
	}
	else if (option == "s" || option == "S") {
		//list last move then give list of options again
		//last move.back.show
		user_input();
	}
	else{
		std::cerr << "Invalid input. Please try again." << std::endl;
		user_input();
	}
}