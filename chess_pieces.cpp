//this is where the pieces funtions are defined from chess_pieces.h
#include "includes.h"
#include "chess_pieces.h"
#include "Chess_board.h"

//functions to convert between array loactions and rank and file coordinates
std::string piece::rank_file_location(int row, int col) {
	std::string piece_location = "a1"; //default example, creates a string of size 2
	piece_location[0] = static_cast<char>(col + 97);
	piece_location[1] = static_cast<char>(row + 49);
	return piece_location;
}
int piece::string_to_rank_int(std::string location) {//think of a better name
		//maybe size_t
	int rank = 9 - (location[1] - '0'); //row
	return rank;
}
int piece::string_to_file_int(std::string location) {
	//maybe size_t
	int file = (int)tolower(location[0]) - 96;//column
	return file;
}
//piece colour
int piece::piece_colour() { return 2; }
int queen::piece_colour() { return colour; }
int king::piece_colour() { return colour; }
int bishop::piece_colour() { return colour; }
int knight::piece_colour() { return colour; }
int rook::piece_colour() { return colour; }
int pawn::piece_colour() { return colour; }
int empty::piece_colour() { return 2; }//just not 0 or 1

//setting the piece icons p/P for pawn, - for an empty space etc.
char piece::icon() {
	return '-';
}
char queen::icon() { return piece_icon; }
char king::icon() { return piece_icon; }
char bishop::icon() { return piece_icon; }
char knight::icon() { return piece_icon; }
char rook::icon() { return piece_icon; }
char pawn::icon() { return piece_icon; }
char empty::icon() { return piece_icon; }
//setting pieces names
std::string piece::name() { 
	std::string piece_name = "empty square";
	return piece_name; 
}
std::string queen::name() { return piece_name; }
std::string king::name() { return piece_name; }
std::string bishop::name() { return piece_name; }
std::string knight::name() { return piece_name; }
std::string rook::name() { return piece_name; }
std::string pawn::name() { return piece_name; }
std::string empty::name() { return piece_name; }
//number of moves made
int piece::number_of_moves_made() { return 0; }
int queen::number_of_moves_made() { return number_of_moves; }
int king::number_of_moves_made() { return number_of_moves; }
int bishop::number_of_moves_made() { return number_of_moves; }
int knight::number_of_moves_made() { return number_of_moves; }
int rook::number_of_moves_made() { return number_of_moves; }
int pawn::number_of_moves_made() { return number_of_moves; }
//ading to the number of moves made
void piece::piece_move() {};
void queen::piece_move() { number_of_moves++; }
void king::piece_move() { number_of_moves++; }
void bishop::piece_move() { number_of_moves++; }
void knight::piece_move() { number_of_moves++; }
void rook::piece_move() { number_of_moves++; }
void pawn::piece_move() { number_of_moves++; }
//is the pawn taking a piece
//piece
bool piece::valid_move(std::string location, std::string destination, bool take_piece) { return 0; }
//queen
bool queen::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = abs(string_to_rank_int(destination) - string_to_rank_int(location));
	int file_move_distance = abs(string_to_file_int(destination) - string_to_file_int(location));
	if ((rank_move_distance == 0 && file_move_distance > 0 && file_move_distance <= 8) || (file_move_distance == 0 && rank_move_distance > 0 && rank_move_distance <= 8) || (rank_move_distance == file_move_distance && rank_move_distance > 0 && file_move_distance > 0 && rank_move_distance <= 8 && file_move_distance <= 8)) {
		//queen can move in straight lines and diagonals 
		//but not through pieces, need to have a check for that
		return 1;
	}
	else { return 0; }
}
//king
bool king::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = abs(string_to_rank_int(destination) - string_to_rank_int(location));
	int file_move_distance = abs(string_to_file_int(destination) - string_to_file_int(location));
	//can move only one square but in any direction
	if (rank_move_distance == 1 || file_move_distance == 1) {
		return 1;
	}
	else { return 0; }
}
//bishop
bool bishop::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = abs(string_to_rank_int(destination) - string_to_rank_int(location));
	int file_move_distance = abs(string_to_file_int(destination) - string_to_file_int(location));
	//can move only diagonals
	if (rank_move_distance == file_move_distance && rank_move_distance > 0 && file_move_distance > 0) {
		return 1;
	}
	else { return 0; }
}
//knight
bool knight::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = abs(string_to_rank_int(destination) - string_to_rank_int(location));
	int file_move_distance = abs(string_to_file_int(destination) - string_to_file_int(location));
	//can move in L shapes
	if ((rank_move_distance == 2 && file_move_distance == 1)||(rank_move_distance == 1 && file_move_distance == 2)) {
		return 1;
	}
	else { return 0; }
}
//rook
bool rook::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = abs(string_to_rank_int(destination) - string_to_rank_int(location));
	int file_move_distance = abs(string_to_file_int(destination) - string_to_file_int(location));
	//can move only straight lines
	if ((rank_move_distance == 0 && file_move_distance > 0 )|| (file_move_distance == 0 && rank_move_distance > 0)) {
		return 1;
	}
	else { return 0; }
}
//pawn
bool pawn::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = string_to_rank_int(destination) - string_to_rank_int(location);
	int file_move_distance = abs(string_to_file_int(destination) - string_to_file_int(location));
	//can move 1 square forward, 2 if its the first go. can take diagonal
	//can only go in one direction 
	if (rank_move_distance < 0 && piece_colour() == 0) {
		if (number_of_moves == 0 && rank_move_distance == -2 && file_move_distance == 0 && take_piece == false) {return 1;}
		else if (rank_move_distance == -1 && file_move_distance == 0 && take_piece == false) { return 1; }
		else if (rank_move_distance == -1 && file_move_distance == 1 && take_piece == true) {return 1;}
		else { return 0; }
	}
	else if (rank_move_distance > 0 && piece_colour() == 1) {
		if (number_of_moves == 0 && rank_move_distance == 2 && file_move_distance == 0 && take_piece == false) { return 1; }
		else if (rank_move_distance == 1 && file_move_distance == 0 && take_piece == false) { return 1; }
		else if (rank_move_distance == 1 && file_move_distance == 1 && take_piece == true) { return 1; }
		else { return 0; }
	}
	else { return 0; }
}
//empty


