//function definitions for board.h
#include "includes.h"
#include "chess_pieces.h"
#include "Chess_board.h"

//board functions
int board::king_in_check() {
	//interate though and if king is in check
	std::cout << "Black is in check" << std::endl;
	return 0;
}
//bool checkmate() { return 1; }
//move pieces functions
//swaps the piece with an empty one
void board::swap_piece(std::string location, std::string destination) {
	list_of_moves_made.push_back(std::string(1, current_board[index(string_to_rank(location), string_to_file(location))]->icon()) + ":" + location + "->-" + destination);
	current_board[index(string_to_rank(location), string_to_file(location))]->piece_move();
	piece* temp = current_board[index(string_to_rank(destination), string_to_file(destination))];
	current_board[index(string_to_rank(destination), string_to_file(destination))] = current_board[index(string_to_rank(location), string_to_file(location))];
	current_board[index(string_to_rank(location), string_to_file(location))] = temp;
}
void board::take_piece(std::string location, std::string destination) {
	list_of_moves_made.push_back(std::string(1, current_board[index(string_to_rank(location), string_to_file(location))]->icon()) + ":" + location + "->X" + destination);
	current_board[index(string_to_rank(location), string_to_file(location))]->piece_move();
	taken_pieces.push_back(current_board[index(string_to_rank(destination), string_to_file(destination))]);
	current_board[index(string_to_rank(destination), string_to_file(destination))] = current_board[index(string_to_rank(location), string_to_file(location))];
	current_board[index(string_to_rank(location), string_to_file(location))] = new empty();
}
void board::castling(std::string location, std::string destination) {
	std::cout << "Castling!" << std::endl;
	list_of_moves_made.push_back(std::string(1, current_board[index(string_to_rank(location), string_to_file(location))]->icon()) + ":" + location + "->C" + destination);
	current_board[index(string_to_rank(location), string_to_file(location))]->piece_move();
	piece* temp = current_board[index(string_to_rank(destination), string_to_file(destination))];
	current_board[index(string_to_rank(destination), string_to_file(destination))] = current_board[index(string_to_rank(location), string_to_file(location))];
	current_board[index(string_to_rank(location), string_to_file(location))] = temp;
}
void board::promotion(std::string location, std::string destination) {
	std::cout << " Pawn gets promoted to a Queen!" << std::endl;
	list_of_moves_made.push_back(std::string(1, current_board[index(string_to_rank(location), string_to_file(location))]->icon()) + ":" + location + "->Q" + destination);
	current_board[index(string_to_rank(destination), string_to_file(destination))] = new queen(current_board[index(string_to_rank(location), string_to_file(location))]->piece_colour());
	current_board[index(string_to_rank(location), string_to_file(location))] = new empty();
}
//function to return the index of the array
int board::index(size_t m, size_t n) const {
	if (m > 0 && m < 9 && n > 0 && n < 9) { return (n - 1) + (m - 1) * 8; }
	else { 
		std::cerr << "Error: out of range. Index not on board" << std::endl;
		return 100;
	}
}
//functions to turn the entered locations into row and column values that 
//can be put into the index function
int board::string_to_file(std::string location) {
	int file = (int)tolower(location[0]) - 96;//column
	return file;
}
int board::string_to_rank(std::string location) {
	int rank = 9 - (location[1] - '0'); //row
	return rank;
}
//function to return whether its black or whites turn
void board::whose_turn() {
	if (current_turn == 0) {
		std::cout << "WHITE players turn (capitals): " << std::endl;
	}
	else {
		std::cout << "BLACK players turn (lowercase): " << std::endl;
	}
}
int board::move_number() { return list_of_moves_made.size(); }
//The move function checks the inputted moves and if it's valid it calls the appropriate move functions.
void board::move() {
	//move entered
	std::string piece_location;
	std::string piece_destination;
	std::cout << "Choose piece you would like to move (example: D2 or g1): ";
	std::cin >> piece_location;
	if (piece_location.length() == 2 && index(string_to_rank(piece_location), string_to_file(piece_location)) != 100) {//check valid entry,add a few more checks
		//checking right players turn, black or white. cant select empty, colour 2.
		if (current_turn == current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->piece_colour()) {
			//std::cout << string_to_rank(piece_location) << ", " << string_to_file(piece_location) << std::endl;
			std::cout << "Piece selected: ";
			std::cout << current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->name() << std::endl;
		}
		else if (current_turn == 2) { 
			std::cout << " You have not selected a piece. Try again." << std::endl; 
			user_input(); 
		}
		else if (current_turn != current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->piece_colour()) {
			std::cout << "Its not your turn." << std::endl;
			//tell them whose go it is
			whose_turn();
			move();
		}
	}
	else { 
		//make sure this works
		std::cout << "please enter a valid piece position:";
		std::cin.clear();
		std::cin >> piece_location;
	}
	//piece has a possiblily of moving // have option to list possible moves here //and then still want to move this piece? Show possible moves<S>
	std::cout << "Move to: ";
	std::cin >> piece_destination;
	//std::cout << string_to_rank(piece_destination) << ", " << string_to_file(piece_destination) << std::endl;
	//move checks performed
	//check if inout is valid
	if (piece_destination.length() == 2 && index(string_to_rank(piece_location), string_to_file(piece_location)) != 100) {
		//checking the path is clear
		//see if there are any pieces in between piece location and destination. only have to consider straight lines or diagonals
		bool path_is_clear = true;
		bool changed_more_than_one_col = false;
		bool changed_more_than_one_row = false;
		if (abs(string_to_file(piece_destination) - string_to_file(piece_location)) > 1) { changed_more_than_one_col = true; }
		if (abs(string_to_rank(piece_destination) - string_to_rank(piece_location)) > 1) { changed_more_than_one_row = true; }
		//for piece travelling along a column
		if ((string_to_file(piece_destination) - string_to_file(piece_location)) == 0 && changed_more_than_one_row == true) {
			//going down 
			if (string_to_rank(piece_destination) > string_to_rank(piece_location)) {
				for (int r{ string_to_rank(piece_location) +1}; r < string_to_rank(piece_destination); r++) {
					if (current_board[index(r, string_to_file(piece_location))]->icon() != '-') {
						path_is_clear = false;
					}
				}
			}
			//going up the board
			else {
				for (int r{ string_to_rank(piece_destination) +1}; r < string_to_rank(piece_location); r++) {
					if (current_board[index(r, string_to_file(piece_location))]->icon() != '-') {
						path_is_clear = false;
					}
				}
			}
		}
		//travelling along a row
		else if ((string_to_rank(piece_destination) - string_to_rank(piece_location)) == 0 && changed_more_than_one_col == true) {
			//going right
			if (string_to_file(piece_destination) > string_to_file(piece_location)) {
				for (int j{ string_to_file(piece_location)+1 }; j < string_to_file(piece_destination); j++) {
					if (current_board[index(string_to_rank(piece_location), j)]->icon() != '-') {
						path_is_clear = false;
					}
				}
			}
			//going left
			else {
				for (int j{ string_to_file(piece_destination) +1}; j < string_to_file(piece_location); j++) {
					if (current_board[index(string_to_rank(piece_location),j)]->icon() != '-') {
						path_is_clear = false;
					}
				}
			}
		}
		//travelling along a diagonal
		else if (abs(string_to_rank(piece_destination) - string_to_rank(piece_location)) == abs(string_to_file(piece_destination) - string_to_file(piece_location)) && changed_more_than_one_row == true && changed_more_than_one_col == true) {
			//going down the board
			if (string_to_rank(piece_destination) > string_to_rank(piece_location)) {
				//going left
				if (string_to_file(piece_destination) > string_to_file(piece_location)) {
					int R = string_to_rank(piece_location) + 1;
					for (int j{ string_to_file(piece_location) +1}; j < string_to_file(piece_destination); j++) {
						if (current_board[index(R, j)]->icon() != '-') {
								path_is_clear = false;
						}
						R++;
					}
				}
				//going right
				else {
					int R = string_to_rank(piece_location) + 1;
					for (int j{ string_to_file(piece_destination)+1 }; j < string_to_file(piece_location); j++) {
						if (current_board[index(R, j)]->icon() != '-') {
								path_is_clear = false;
						}
						R++;
					}
				}
			}
			//going up the board
			else if(string_to_rank(piece_destination) < string_to_rank(piece_location)){
				for (int i{ string_to_rank(piece_destination) }; i < string_to_rank(piece_location); i++) {
					if (string_to_file(piece_destination) > string_to_file(piece_location)) {
						for (int j{ string_to_file(piece_location) }; j < string_to_file(piece_destination); j++) {
							if (current_board[index(i, j)]->icon() != '-') {
								path_is_clear = false;
							}
						}
					}
					else {
						for (int j{ string_to_file(piece_destination) }; j < string_to_file(piece_location); j++) {
							if (current_board[index(i, j)]->icon() != '-') {
								path_is_clear = false;
							}
						}
					}
				}
			}
		}
		if(path_is_clear == false){ 
			std::cout << " Path is not clear. Please try another move." << std::endl;
			move();
		}
		else {
			//check if destination square is empty
			if (current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))]->icon() == '-') {
				if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->valid_move(piece_location, piece_destination, 0)) {
					if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->name() == "pawn" && (string_to_rank(piece_destination) == 8 || string_to_rank(piece_destination) == 1)) {
						//pawn promotion
						promotion(piece_location, piece_destination);
					}
					else {
						//swap
						swap_piece(piece_location, piece_destination);
					}
				}
				else {
					std::cerr << "Invalid move, please try again." << std::endl;
					move();
				}
			}
			//if not check destination piece is on the enemy side
			else if (current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))]->piece_colour() != current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->piece_colour()) {
				if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->valid_move(piece_location, piece_destination, 1)) {
					if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->name() == "pawn" && (string_to_rank(piece_destination) == 8 || string_to_rank(piece_destination) == 1)) {
						//pawn promotion
						promotion(piece_location, piece_destination);
					}
					else {
						//take
						take_piece(piece_location, piece_destination);
					}
				}
				else {
					std::cerr << " Invalid move, please try again." << std::endl;
					move();
				}
			}
			//else check if its a king and rook for castling op
			else if (tolower(current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->icon()) == 'k' && tolower(current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))]->icon()) == 'r') {
				if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->number_of_moves_made() == 0 && current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))]->number_of_moves_made() == 0) {
					//cant be any pieces inbetween, can't castle out of check
					castling(piece_location, piece_destination);
				}
				else {
					std::cout << " You cant castle if you have already moved one of the concerned pieces" << std::endl;
					move();
				}
			}
			else {
				std::cerr << " You can't take your own piece..." << std::endl;
				move();
			}
		}
	}
	else {
		std::cerr << " Invalid destination input, please try again." << std::endl;
		move();
	}
	//current turn update
	current_turn == 0? (current_turn = 1):(current_turn = 0);
	display_board();
	user_input();
}
void board::display_board() {
	std::system("cls");
	std::cout << "\n  Hermione Warr's Chess Game\n\n ";
	whose_turn();
	if (move_number() > 0) {
		std::cout << " Last move: " << list_of_moves_made.back() << std::endl;
	}
	std::cout << "\n      A  B  C  D  E  F  G  H " << std::endl;
	std::cout << "     ------------------------" << std::endl;
	for (size_t irow{1}; irow < 9; irow++) {
		std::cout << "  " << 9 - irow << " |";
		for (size_t jcol{1}; jcol < 9; jcol++) {
			std::cout << " " << current_board[index(irow,jcol)]->icon() << " ";
		}
		std::cout << "| " << 9 - irow << std::endl;
	}
	std::cout << "     ------------------------" << std::endl;
	std::cout << "      A  B  C  D  E  F  G  H " << std::endl;
	std::cout << std::endl;
	//display pieces taken by each player
	if (move_number() > 0) {
		std::cout << " Taken pieces: ";
		//replace with iterators
		if (taken_pieces.size() == 0) {
			std::cout << "no pieces captured yet" << std::endl;
		}
		else {
			bool any_taken_whites = false;
			bool any_taken_blacks = false;
			for (std::vector<piece*>::iterator it = taken_pieces.begin(); it != taken_pieces.end(); it++) {
				if ((*it)->piece_colour() == 0) { any_taken_whites = true; }
				else if ((*it)->piece_colour() == 1) { any_taken_blacks = true; }
			}
			if (any_taken_whites = true) {
				std::cout << "\n\tWHITE captured pieces: ";
				for (std::vector<piece*>::iterator it = taken_pieces.begin(); it != taken_pieces.end(); it++) {
					if ((*it)->piece_colour() == 0) {
						std::cout << (*it)->icon() << " ";
					}
				}
				std::cout << std::endl;
			}
			if (any_taken_blacks == true){
				std::cout << "\tBLACK captured piece: ";
				for (std::vector<piece*>::iterator it = taken_pieces.begin(); it != taken_pieces.end(); it++) {
					if ((*it)->piece_colour() == 1) {
						std::cout << (*it)->icon() << " ";
					}
				}
			}
		}
		std::cout << std::endl;
	}
	user_input();
}
void board::user_input() {
	std::string option;
	std::cout << " Options:  Move<M>  New game<N>  Quit<Q>  Undo move<U>" << std::endl;
	std::cin >> option;
	if (option == "m" || option == "M") {
		move();
	}
	else if (option == "n" || option == "N") {
		//reset
		number_of_moves = 0;
		current_turn = 0;
		std::cout << "Starting new game!\n" << std::endl;
		delete current_board;
		new board();
		display_board();
	}
	else if (option == "q" || option == "Q") {
		std::string quit;
		std::cout << " Are you sure? (y/n)" << std::endl;
		std::cin >> quit;
		if (quit == "y" || quit == "yes") {
			//quit game
			std::cout << "See you next time!" << std::endl;
			std::cout << "Quitting game" << std::endl;
			exit(0);
		}
		else if (quit == "n" || quit == "N") {
			user_input();
		}
		do {
			std::cout << "Pease enter y or n" << std::endl;
			std::cin >> quit;
		} while (quit != "y" || quit != "yes" || quit != "n" || quit != "no");
	}
	else if (option == "u" || option == "U") {
		//undo move

	}
	else {
		std::cerr << "Invalid input. Please try again." << std::endl;
		user_input();
	}
}
//constructor
board::board() {
	//set up the starting board
	try {
		//black pieces
		current_board[0] = new rook(1);
		current_board[1] = new knight(1);
		current_board[2] = new bishop(1);
		current_board[3] = new queen(1);
		current_board[4] = new king(1);
		current_board[5] = new bishop(1);
		current_board[6] = new knight(1);
		current_board[7] = new rook(1);
		for (int i{ 8 }; i < 16; i++) {
			current_board[i] = new pawn(1);
		}
		for (int i{ 16 }; i < 48; i++) {
			current_board[i] = new empty();
		}
		//white pieces
		for (int i{ 48 }; i < 56; i++) {
			current_board[i] = new pawn(0);
		}
		current_board[56] = new rook(0);
		current_board[57] = new knight(0);
		current_board[58] = new bishop(0);
		current_board[59] = new queen(0);
		current_board[60] = new king(0);
		current_board[61] = new bishop(0);
		current_board[62] = new knight(0);
		current_board[63] = new rook(0);
	}
	catch (std::out_of_range e) {
		std::cerr << "current board out of range" << std::endl;
	}