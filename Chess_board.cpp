//function definitions for board.h
#include "includes.h"
#include "chess_pieces.h"
#include "Chess_board.h"

template<class T>
void print_vector(std::vector<T> const& vec) {
	for (T element : vec) {
		std::cout << element << std::endl;
	}
}
void pause(){
	std::cout << "Press enter to go to next move.";
	std::cin.get();
}
//board functions
//save/load game function
void board::save_game() {
	std::string game_file_name;
	std::cout << "Please enter the name of the game you want to save (no extension): ";
	std::cin >> game_file_name;
	game_file_name += ".txt";
	std::ofstream game_file(game_file_name);
	if (game_file.is_open()) {
		std::cout << "Saving game..." << std::endl;
		for (std::vector<std::string>::iterator it = list_of_moves_made.begin(); it != list_of_moves_made.end(); it++) {
			game_file << *it << "\n";
		}
		game_file.close();
		std::cout << "Your game has been saved as: " << game_file_name << std::endl;
	}
	else {
		std::cout << "Unable to save game, sorry!" << std::endl;
	}
	return;
}
void board::load_game() {
	std::string load_file_name;
	std::cout << "Please enter the name of the game you want to load (no extension needed)" << std::endl;
	std::cin >> load_file_name; 
	load_file_name += ".txt";
	std::ifstream load_file(load_file_name);
	std::string each_move;
	current_turn = 0;
	if (load_file.is_open()) {
		std::cout << "Loading game..." << std::endl;
		pause();//this takes the previous enter
		display_board();
		pause(); 
		while (std::getline(load_file, each_move)) {
			std::string piece_location;
			piece_location += each_move.at(2);
			piece_location += each_move.at(3);
			std::string piece_destination;
			piece_destination += each_move.at(7);
			piece_destination += each_move.at(8);
			move(piece_location, piece_destination);
			pause();
		}
	}
	else {
		std::cerr << "Error loading file." << std::endl;
		return;
	}
}
void board::show_game() {
	print_vector(list_of_moves_made);
}
bool board::checkmate() {
	//interate though and see if one move could get king out of check
	//perform every possible move by every friendly piece and then check if king is still in check. 
	std::string king_location;
	int king_index{};
	int vector_index{};
	for (std::vector<std::shared_ptr<piece>>::iterator it = current_board.begin(); it != current_board.end(); it++, vector_index++) {
		if ((*it)->name() == "King" && (*it)->piece_colour() == current_turn) {
			king_location = rank_file_string_coordinate(vector_index);
			king_index = vector_index;
		}
	}
	//perform every possible move by every friendly piece and then check if king is still in check.  
	int i{};
	for (std::vector<std::shared_ptr<piece>>::iterator it = current_board.begin(); it != current_board.end(); it++, i++) {
		if ((*it)->piece_colour() == current_turn) {
			std::string it_location = rank_file_string_coordinate(i);
			std::vector<std::string> help_output = help(it_location);
			if (help_output.size() != 0) { return false; }
		}
	}
	return true;
}
bool board::king_in_check() {
	std::string king_location;
	int vector_index{};
	for (std::vector<std::shared_ptr<piece>>::iterator it = current_board.begin(); it != current_board.end(); it++, vector_index++) {
		//check whose turn and find their king
		if ((*it)->name() == "King" && (*it)->piece_colour() == current_turn) {
			king_location = rank_file_string_coordinate(vector_index);
		}
	}
	int index{};
	//look at the valid moves for each piece on the board and see if any of them can take the king
	for (std::vector<std::shared_ptr<piece>>::iterator it = current_board.begin(); it != current_board.end(); it++,index++) {
		if ((*it)->piece_colour() != current_turn && (*it)->valid_move(rank_file_string_coordinate(index), king_location, 1) 
			&& is_path_clear(rank_file_string_coordinate(index), king_location)) {
			return 1;
		}
	}
	return 0;
}
//help funtion
std::vector<std::string> board::help(std::string location) {
	int j{};
	std::vector<std::string> destinations;
	int location_index = index(string_to_rank(location), string_to_file(location));
	for (std::vector<std::shared_ptr<piece>>::iterator it_des = current_board.begin(); it_des != current_board.end(); it_des++, j++) {
		std::string destination = rank_file_string_coordinate(j);
		if (location != destination) {
			//find all moves player can make from that location. cant move into check
			if ((*it_des)->piece_colour() != current_turn && is_path_clear(location, destination) == true) {
				if (current_board[location_index]->name() == "King" && (*it_des)->icon() == '-' && abs(string_to_file(destination) - string_to_file(location)) == 2 && castling_possible(location, destination) == true) {
					castling(location, destination);
					if(king_in_check() == false){ destinations.push_back(destination); }
					undo_move();
				}
				if ((*it_des)->icon() == '-' && current_board[location_index]->valid_move(location, destination, 0)) {
					if (current_board[location_index]->name() == "Pawn" && (string_to_rank(destination) == 8 || string_to_rank(destination) == 1)) {
						//pawn promotion
						promotion(location, destination);
						if (king_in_check() == false) { destinations.push_back(destination); }
						undo_move();
					}
					else {
						//swap
						bool undoing_move = false;
						swap_piece(location, destination, undoing_move);
						if (king_in_check() == false) { destinations.push_back(destination); }
						undo_move();
					}
				}
				else if ((*it_des)->icon() != '-' && current_board[location_index]->valid_move(location, destination, 1)) {
					if (current_board[location_index]->name() == "Pawn" && (string_to_rank(destination) == 8 || string_to_rank(destination) == 1)) {
						//pawn promotion
						promotion(location, destination);
						if (king_in_check() == false) { destinations.push_back(destination); }
						undo_move();
					}
					else {//take
						take_piece(location, destination);
						if (king_in_check() == false) { destinations.push_back(destination); }
						undo_move();
					}
				}
				
			}
		}
	}
	return destinations;
}
//move pieces functions
void board::swap_piece(std::string location, std::string destination, bool undo_move) {
	//swaps the piece with an empty one
	if (undo_move == false) {
		current_board[index(string_to_rank(location), string_to_file(location))]->piece_move();
		list_of_moves_made.push_back(std::string(1, current_board[index(string_to_rank(location), string_to_file(location))]->icon()) + ":" + location + "->-" + destination);
	}
	else if (undo_move == true && list_of_moves_made.size() != 0){
		current_board[index(string_to_rank(location), string_to_file(location))]->undo_piece_move();
		list_of_moves_made.pop_back();
	}
	std::shared_ptr<piece> temp = current_board[index(string_to_rank(destination), string_to_file(destination))];
	current_board[index(string_to_rank(destination), string_to_file(destination))] = current_board[index(string_to_rank(location), string_to_file(location))];
	current_board[index(string_to_rank(location), string_to_file(location))] = temp;
}
void board::take_piece(std::string location, std::string destination) {
	//take piece and replace original pointer with one to an empty
	list_of_moves_made.push_back(std::string(1, current_board[index(string_to_rank(location), string_to_file(location))]->icon()) + ":" + location + "->X" + destination);
	current_board[index(string_to_rank(location), string_to_file(location))]->piece_move();
	taken_pieces.push_back(current_board[index(string_to_rank(destination), string_to_file(destination))]);
	current_board[index(string_to_rank(destination), string_to_file(destination))] = current_board[index(string_to_rank(location), string_to_file(location))];
	current_board[index(string_to_rank(location), string_to_file(location))] = std::make_shared<empty>();
}
void board::castling(std::string location, std::string destination) {
	//swaps king and rook 
	std::cout << "Castling!" << std::endl;
	list_of_moves_made.push_back(std::string(1, current_board[index(string_to_rank(location), string_to_file(location))]->icon()) + ":" + location + "->C" + destination);
	current_board[index(string_to_rank(location), string_to_file(location))]->piece_move();
	//move the king
	current_board[index(string_to_rank(destination), string_to_file(destination))] = current_board[index(string_to_rank(location), string_to_file(location))];
	current_board[index(string_to_rank(location), string_to_file(location))] = std::make_shared<empty>();
	//move the rook
	if (string_to_file(destination) > 5) {//king side
		current_board[index(string_to_rank(location), (string_to_file(location) + 1))] = current_board[index(string_to_rank(location), (string_to_file(location) + 3))];
		current_board[index(string_to_rank(location), (string_to_file(location) + 3))] = std::make_shared<empty>();
	}
	else {//queen side
		current_board[index(string_to_rank(location), (string_to_file(location) - 1))] = current_board[index(string_to_rank(location), (string_to_file(location) - 4))];
		current_board[index(string_to_rank(location), (string_to_file(location) - 4))] = std::make_shared<empty>();
	}
}
void board::promotion(std::string location, std::string destination) {
	//once pawn reached end of board gets upgraded to queen
	std::cout << "Pawn gets promoted to a Queen!" << std::endl;
	list_of_moves_made.push_back(std::string(1, current_board[index(string_to_rank(location), string_to_file(location))]->icon()) + ":" + location + "->Q" + destination);
	current_board[index(string_to_rank(destination), string_to_file(destination))] = std::make_shared<queen>(current_board[index(string_to_rank(location), string_to_file(location))]->piece_colour());
	current_board[index(string_to_rank(location), string_to_file(location))] = std::make_shared<empty>();
}
void board::undo_move() {
	bool undo = true;
	std::string last_move = list_of_moves_made.back();
	char move_type = last_move.at(6);
	std::string piece_location;
	piece_location += last_move.at(2);
	piece_location += last_move.at(3);
	std::string piece_destination; 
	piece_destination += last_move.at(7);
	piece_destination += last_move.at(8);
	char piece_icon = last_move.at(0);
	if (move_type == '-') { 
		swap_piece(piece_destination, piece_location, undo); 
	}
	else if(move_type == 'X'){
		//undo take
		swap_piece(piece_destination, piece_location, undo);
		current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))] = taken_pieces.back();
		taken_pieces.pop_back();
	}
	else if(move_type == 'C' ){
		current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))]->undo_piece_move();
		//move the king
		current_board[index(string_to_rank(piece_location), string_to_file(piece_location))] = current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))];
		current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))] = std::make_shared<empty>();
		//move the rook
		if (string_to_file(piece_destination) > 5) {//king side
			current_board[index(string_to_rank(piece_location), string_to_file(piece_location) + 3)] = current_board[index(string_to_rank(piece_location), string_to_file(piece_location) + 1)];
			current_board[index(string_to_rank(piece_location), string_to_file(piece_location) + 1)] = std::make_shared<empty>();
		}
		else {//queen side
			current_board[index(string_to_rank(piece_location), string_to_file(piece_location) - 4)] = current_board[index(string_to_rank(piece_location), string_to_file(piece_location) - 1)];
			current_board[index(string_to_rank(piece_location), string_to_file(piece_location) - 1)] = std::make_shared<empty>();
		}
		list_of_moves_made.pop_back();
	}
	else if (move_type == 'Q') {
		current_board[index(string_to_rank(piece_location), string_to_file(piece_location))] = std::make_shared<pawn>(current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))]->piece_colour());
		current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))] = std::make_shared <empty>();
		list_of_moves_made.pop_back();
	}
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
//can be put into the index function and vice versa
int board::string_to_file(std::string location) {
	int file = (int)tolower(location[0]) - 96;//column
	return file;
}
int board::string_to_rank(std::string location) {
	int rank = 9 - (location[1] - '0'); //row
	return rank;
}
std::string board::rank_file_string_coordinate(int vector_index) {
	//0 = 48, 8 = 56, a = 97, h = 104
	int count{};
	int col{}; 
	int row{};
	for (int i{}; i <= vector_index; i++) { 
		if (i % 8 == 0 && i>0) { count++; } 
	}
	col = (vector_index) - 8 * (count);
	row = 8-count;
	std::string piece_location = "a1"; //default example, creates a string of size 2
	piece_location[0] = static_cast<char>(col + 97);
	piece_location[1] = static_cast<char>(row + 48);
	return piece_location;
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
std::string board::return_current_turn() {
	if (current_turn == 0) { std::string current_go = "WHITE"; return current_go; }
	else { std::string current_go = "BLACK"; return current_go; }
}
int board::move_number() { return list_of_moves_made.size(); }
//The move function checks the inputted moves and if it's valid it calls the appropriate move functions.
void board::move_input() {
	//move entered
	std::string piece_location;
	std::string piece_destination;
	std::cout << "Choose piece you would like to move (example: D2 or g1): ";
	std::cin >> piece_location;
	if (piece_location.length() == 2 && index(string_to_rank(piece_location), string_to_file(piece_location)) != 100) {//check valid entry,add a few more checks
		//checking right players turn, black or white. cant select empty, colour 2.
		if (current_turn == current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->piece_colour()) {
			std::cout << "Piece selected: ";
			std::cout << current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->name() << std::endl;
		}
		else if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->piece_colour() == 2) {
			std::cout << "You have not selected a piece. Try again." << std::endl;
			user_input();
			return;
		}
		else if (current_turn != current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->piece_colour()) {
			std::cout << "Its not your turn." << std::endl;
			//tell them whose go it is
			whose_turn();
			move_input();
			return;
		}
	}
	else {
		std::cout << "Please enter a valid piece position: ";
		move_input();
		return;
	}
	std::cout << "Enter <H> for help or enter piece destination: ";
	std::cin >> piece_destination;
	if ((piece_destination == "h" || piece_destination == "H") && piece_destination.length() == 1) {
		std::vector<std::string> help_output = help(piece_location);
		if (help_output.size() == 0) { std::cout << "No possible moves. Choose another piece to move." << std::endl; move_input(); }
		else {
			std::cout << "List of possible moves for selected piece: " << std::endl;
			print_vector(help_output);//template calls
			piece_destination.clear();
			std::cout << "Enter piece destination: ";
			std::cin >> piece_destination;
		}
	}
	if (piece_destination.length() == 2 && index(string_to_rank(piece_location), string_to_file(piece_location)) != 100) {
		//checking the path is clear
		//see if there are any pieces in between piece location and destination. only have to consider straight lines or diagonals
		if (is_path_clear(piece_location, piece_destination) == false) {
			std::cout << " Path is not clear. Please try another move." << std::endl;
			move_input();
			return;
		}
		move(piece_location, piece_destination);
	}
	else {
		std::cerr << " Invalid destination input, please try again." << std::endl;
		move_input();
		return;
	}
}
bool board::move(std::string location, std::string destination) {
	//move entered
	std::string piece_location = location;
	std::string piece_destination = destination;
	//else check if its a king and rook for castling op
	if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->name() == "King" && current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))]->icon() == '-' && king_in_check() == false && abs(string_to_file(piece_destination)-string_to_file(piece_location))==2) {
		if (castling_possible(piece_location, piece_destination) == true) {
			//cant be any pieces inbetween, can't castle out of check
			castling(piece_location, piece_destination);
		}
		else {
			move_input();
		}
	}
	//check if destination square is empty
	else if (current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))]->icon() == '-') {
		if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->valid_move(piece_location, piece_destination, 0)) {
			if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->name() == "Pawn" && (string_to_rank(piece_destination) == 8 || string_to_rank(piece_destination) == 1)) {
				//pawn promotion
				promotion(piece_location, piece_destination);
			}
			else {
				//swap
				bool undo = false;
				swap_piece(piece_location, piece_destination, undo);
			}
		}
		else {
			std::cerr << "Invalid move, please try again." << std::endl;
			move_input();
			return false;
		}
	}
	//if not check destination piece is on the enemy side
	else if (current_board[index(string_to_rank(piece_destination), string_to_file(piece_destination))]->piece_colour() != current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->piece_colour()) {
		if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->valid_move(piece_location, piece_destination, 1)) {
			if (current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->name() == "Pawn" && (string_to_rank(piece_destination) == 8 || string_to_rank(piece_destination) == 1)) {
				//pawn promotion
				std::cout << "promoting" << std::endl;
				promotion(piece_location, piece_destination);
			}
			else {
				//take
				take_piece(piece_location, piece_destination);
			}
		}
		else {
			std::cerr << " Invalid move, please try again." << std::endl;
			move_input();
			return false;
		}
		}
	else {
		std::cerr << "You can't take your own piece..." << std::endl;
		move_input();
		return false;
	}
	//see if person is in check
	if (king_in_check() == true) {
		std::cout << "You cannot move into check." << std::endl;
		std::cout << "Please try another move." << std::endl;
		undo_move();
		move_input();
		return false;
	}
	//current turn update
	current_turn = (move_number() % 2);
	//update the board
	display_board();
	//offer option of saving your game.
	if (king_in_check() == true && checkmate() == true ) {
		game_over = true;
		std::cout << "Do you want to save this game? (y/n)" << std::endl;
		std::string save;
		std::cin >> save;
		if (save == "y" || save == "Y") {
			save_game();
		}
	}
	return game_over;
}
void board::display_board() {
	std::system("cls");
	std::cout << "\n  Hermione Warr's Chess Game\n" << std::endl;
	if (checkmate() == true) { 
		std::cout << "Checkmate!" << std::endl; 
	}
	else {
		whose_turn();
		if (king_in_check() == true) { std::cout << return_current_turn() << "Player is in check" << std::endl; }
	}
	if (move_number() > 0) {
		std::cout << "Last move: " << list_of_moves_made.back() << std::endl;
		cool_move();
	}
	std::cout << "\n      A  B  C  D  E  F  G  H " << std::endl;
	std::cout << "     ------------------------" << std::endl;
	for (size_t irow{ 1 }; irow < 9; irow++) {
		std::cout << "  " << 9 - irow << " |";
		for (size_t jcol{ 1 }; jcol < 9; jcol++) {
			std::cout << " " << current_board[index(irow, jcol)]->icon() << " ";
		}
		std::cout << "| " << 9 - irow << std::endl;
	}
	std::cout << "     ------------------------" << std::endl;
	std::cout << "      A  B  C  D  E  F  G  H " << std::endl;
	std::cout << std::endl;
	//display pieces taken by each player
	if (move_number() > 0) {
		std::cout << " Taken pieces: ";
		if (taken_pieces.size() == 0) {
			std::cout << "no pieces captured yet" << std::endl;
		}
		else {
			bool any_taken_whites = false;
			bool any_taken_blacks = false;
			for (std::vector<std::shared_ptr<piece>>::iterator it = taken_pieces.begin(); it != taken_pieces.end(); it++) {
				if ((*it)->piece_colour() == 0) { any_taken_whites = true; }
				else if ((*it)->piece_colour() == 1) { any_taken_blacks = true; }
			}
			if (any_taken_whites = true) {
				std::cout << "\n\tWHITE captured pieces: ";
				//using lambdas to print out taken pieces
				std::for_each(taken_pieces.begin(), taken_pieces.end(),
					[](std::shared_ptr<piece> element) {
						if (element->piece_colour() == 0) { std::cout << element->icon() << " "; }
					});
				std::cout << std::endl;
			}
			if (any_taken_blacks == true) {
				std::cout << "\tBLACK captured piece: ";
				std::for_each(taken_pieces.begin(), taken_pieces.end(),
					[](std::shared_ptr<piece> element) {
						if (element->piece_colour() == 1) { std::cout << element->icon() << " "; }
					});
			}
		}
		std::cout << std::endl;
	} 
}
void board::user_input() {
	std::string option;
	std::cout << "Options:  New game<N>  Move<M>  Quit<Q>  Undo move<U>  Load game<L>  Save game<S>" << std::endl;
	std::cin >> option;
	if (option == "m" || option == "M" ) {
		if(game_in_play == true ||move_number() > 0){ move_input(); }
		else { std::cout << "Must be a game in play to move." << std::endl; user_input(); }
	}
	else if (option == "n" || option == "N" && move_number() == 0) {
		//reset
		/*list_of_moves_made.clear();
		taken_pieces.clear();
		current_turn = 0;
		current_board = nullptr;
		std::cout << "Starting new game!\n" << std::endl;
		board();*/
		game_in_play = true;
		display_board();
	}
	else if (option == "q" || option == "Q") {
		std::string quit;
		std::cout << "Are you sure? (y/n)" << std::endl;
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
	else if ((option == "u" || option == "U") && move_number() > 0) {
		undo_move();
		current_turn == 0 ? (current_turn = 1) : (current_turn = 0);
		display_board();
	}
	else if ((option == "s" || option == "S") && move_number() > 0) {
		save_game();
	}
	else if ((option == "l" || option == "L") && move_number() == 0) {
		load_game();
	}
	else {
		std::cerr << "Invalid input. Please try again." << std::endl;
		return;
	}
}
//constructor
board::board() {
	//set up the starting board
	try {
		//black pieces
		current_board.push_back(std::make_shared <rook>(1));
		current_board.push_back(std::make_shared <knight>(1));
		current_board.push_back(std::make_shared <bishop>(1));
		current_board.push_back(std::make_shared <queen>(1));
		current_board.push_back(std::make_shared <king>(1));
		current_board.push_back(std::make_shared <bishop>(1));
		current_board.push_back(std::make_shared <knight>(1));
		current_board.push_back(std::make_shared <rook>(1));
		for (int i{ 8 }; i < 16; i++) {
			current_board.push_back(std::make_shared <pawn>(1)); i;
		}
		for (int i{ 16 }; i < 48; i++) {
			current_board.push_back(std::make_shared <empty>()); i;
		}
		//white pieces
		for (int i{ 48 }; i < 56; i++) {
			current_board.push_back(std::make_shared <pawn>(0)); i;
		}
		current_board.push_back(std::make_shared <rook>(0));
		current_board.push_back(std::make_shared <knight>(0));
		current_board.push_back(std::make_shared <bishop>(0));
		current_board.push_back(std::make_shared <queen>(0));
		current_board.push_back(std::make_shared <king>(0));
		current_board.push_back(std::make_shared <bishop>(0));
		current_board.push_back(std::make_shared <knight>(0));
		current_board.push_back(std::make_shared <rook>(0));
	}
	catch (std::bad_alloc memory_fail) {
		std::cerr << "Current board memory allocation failure." << std::endl;
		exit(0);
	}
}
void board::cool_move() {
	std::string last_move = list_of_moves_made.back();
	char move_type = last_move.at(6);
	if(move_type == 'Q'){ std::cout << "Advaced move detected: Pawn Promotion!" << std::endl;}
	else if (move_type == 'C') { std::cout << "Advanced move detected: Castling!" << std::endl; }
}
//castling conditions
bool board::castling_possible(std::string king_location, std::string king_destination) {
	int file_move = string_to_file(king_destination) - string_to_file(king_location);
	int rook_file_position = +3;
	bool king_side = true;
	if (file_move < 0) { king_side = false; rook_file_position = -4; }
	std::string rook_position = rank_file_string_coordinate(index(string_to_rank(king_location), string_to_file(king_location) + rook_file_position));
	//neither piece can have moved before. Can't be any pieces inbetween. Can't castle out of check
	if (current_board[index(string_to_rank(king_location), string_to_file(king_location))]->number_of_moves_made() == 0 && 
		current_board[index(string_to_rank(king_location), string_to_file(king_location)+rook_file_position)]->number_of_moves_made() == 0 && is_path_clear(king_location, rook_position)) {
		return true;
	}
	return false;
}
//checking a piece can move to the chosen destination
bool board::is_path_clear(std::string piece_location, std::string piece_destination) {
	bool path_is_clear = true;
	bool changed_more_than_one_col = false;
	bool changed_more_than_one_row = false;
	if (abs(string_to_file(piece_destination) - string_to_file(piece_location)) > 1) { changed_more_than_one_col = true; }
	if (abs(string_to_rank(piece_destination) - string_to_rank(piece_location)) > 1) { changed_more_than_one_row = true; }
	//for piece travelling along a column
	if ((string_to_file(piece_destination) - string_to_file(piece_location)) == 0 && changed_more_than_one_row == true) {
		//going down 
		if (string_to_rank(piece_destination) > string_to_rank(piece_location)) {
			for (int r{ string_to_rank(piece_location) + 1 }; r < string_to_rank(piece_destination); r++) {
				if (current_board[index(r, string_to_file(piece_location))]->icon() != '-') {
					path_is_clear = false;
				}
			}
		}
		//going up the board
		else {
			for (int r{ string_to_rank(piece_destination) + 1 }; r < string_to_rank(piece_location); r++) {
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
			for (int j{ string_to_file(piece_location) + 1 }; j < string_to_file(piece_destination); j++) {
				if (current_board[index(string_to_rank(piece_location), j)]->icon() != '-') {
					path_is_clear = false;
				}
			}
		}
		//going left
		else {
			for (int j{ string_to_file(piece_destination) + 1 }; j < string_to_file(piece_location); j++) {
				if (current_board[index(string_to_rank(piece_location), j)]->icon() != '-') {
					path_is_clear = false;
				}
			}
		}
	}
	//travelling along a diagonal
	else if (abs(string_to_rank(piece_destination) - string_to_rank(piece_location)) == abs(string_to_file(piece_destination) - string_to_file(piece_location)) && changed_more_than_one_row == true && changed_more_than_one_col == true) {
		//going down the board
		if (string_to_rank(piece_destination) > string_to_rank(piece_location)) {
			for (int i{ string_to_rank(piece_location) }; i < string_to_rank(piece_destination); i++) {
				//going right
				if (string_to_file(piece_destination) > string_to_file(piece_location)) {
					for (int j{ string_to_file(piece_location) }; j < string_to_file(piece_destination); j++) {
						if (current_board[index(i, j)]->icon() != '-' && current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->valid_move(piece_location, rank_file_string_coordinate(index(i, j)), 0) == true 
							&& abs(string_to_rank(rank_file_string_coordinate(index(i, j))) - string_to_rank(piece_location)) == abs(string_to_file(rank_file_string_coordinate(index(i, j))) - string_to_file(piece_location))) {
							//std::cout << "testy boi";
							path_is_clear = false;
						}

					}
				}
				else {//going left
					for (int j{ string_to_file(piece_destination) +1}; j < string_to_file(piece_location); j++) {
						if (current_board[index(i, j)]->icon() != '-' && current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->valid_move(piece_location, rank_file_string_coordinate(index(i, j)), 0) == true 
							&& abs(string_to_rank(rank_file_string_coordinate(index(i, j))) - string_to_rank(piece_location)) == abs(string_to_file(rank_file_string_coordinate(index(i, j))) - string_to_file(piece_location))) {
							path_is_clear = false;
						}
					}
				}
			}
		}
		//going up the board
		else if (string_to_rank(piece_destination) < string_to_rank(piece_location)) {
			for (int i{ string_to_rank(piece_destination) +1}; i < string_to_rank(piece_location); i++) {
				if (string_to_file(piece_destination) > string_to_file(piece_location)) {
					for (int j{ string_to_file(piece_location) }; j < string_to_file(piece_destination); j++) {
						if (current_board[index(i, j)]->icon() != '-' && current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->valid_move(piece_location, rank_file_string_coordinate(index(i,j)),0) == true 
							&& abs(string_to_rank(rank_file_string_coordinate(index(i, j))) - string_to_rank(piece_location)) == abs(string_to_file(rank_file_string_coordinate(index(i,j))) - string_to_file(piece_location))) {
							//right
							path_is_clear = false;
						}
					}
				}
				else {
					for (int j{ string_to_file(piece_destination) +1}; j < string_to_file(piece_location); j++) {
						if (current_board[index(i, j)]->icon() != '-' && current_board[index(string_to_rank(piece_location), string_to_file(piece_location))]->valid_move(piece_location, rank_file_string_coordinate(index(i, j)),0) == true 
							&& abs(string_to_rank(rank_file_string_coordinate(index(i, j))) - string_to_rank(piece_location)) == abs(string_to_file(rank_file_string_coordinate(index(i, j))) - string_to_file(piece_location))) {
							//left
							path_is_clear = false;
						}
					}
				}
			}
		}
	}
	return path_is_clear;
}
//typedef std::map<int, std::string> location_in_board_vector;
/*void board::search_board_vector(location_in_board_vector& the_board, int vector_index) {
	location_in_board_vector::iterator board_vector_iter;
	try {
		board_vector_iter = the_board.find(vector_index);
		std::cout << vector_index << board_vector_iter->second << std::endl;
	}
	catch (std::out_of_range e) {
		std::cerr << "index not in board" << std::endl;
	}
}
std::string board::board_setup() {
	//map? //0=48,8=56, a=97, h=104
	location_in_board_vector the_board;
	for (int i{}; i < 64; i++) {
		the_board.insert(std::pair <int, std::string >(i , rank_file_string_coordinate()));
	}
	int vector_index(12);
	search_board_vector(the_board, vector_index);
}*/