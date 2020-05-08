//this is where the pieces funtions are defined from chess_pieces.h
#include "includes.h"
#include "chess_pieces.h"
#include "Chess_board.h"

//functions to convert between string loactions and rank and file coordinates
int string_to_file(std::string location) {
	int file = (int)tolower(location[0]) - 96;//column
	return file;
}
int string_to_rank(std::string location) {
	int rank = 9 - (location[1] - '0'); //row
	return rank;
}
/*--------------------------------------------
			Piece functions
---------------------------------------------*/
//piece constructors
queen::queen(int Q_colour) : piece{} {
	piece_name = "Queen";
	switch (colour = Q_colour) {
	case  0:
		//uppercase for white
		piece_icon = 'Q';
		break;
	case 1:
		//lowercase for black
		piece_icon = 'q';
		break;
	}
}
king::king(int K_colour) : piece{} {
	piece_name = "King";
	switch (colour = K_colour) {
	case  0:
		piece_icon = 'K';
		break;
	case 1:
		piece_icon = 'k';
		break;
	}
}
bishop::bishop(int B_colour) : piece{} {
	piece_name = "Bishop";
	switch (colour = B_colour) {
	case  0:
		piece_icon = 'B';
		break;
	case 1:
		piece_icon = 'b';
		break;
	}
}
knight::knight(int K_colour) : piece{} {
	piece_name = "Knight";
	switch (colour = K_colour) {
	case  0:
		piece_icon = 'N';
		break;
	case 1:
		piece_icon = 'n';
		break;
	}
}
rook::rook(int R_colour) : piece{} {
	piece_name = "Rook";
	switch (colour = R_colour) {
	case  0:
		piece_icon = 'R';
		break;
	case 1:
		piece_icon = 'r';
		break;
	}
}
pawn::pawn(int p_colour) : piece{} {
	piece_name = "Pawn";
	switch (colour = p_colour) {
	case  0:
		piece_icon = 'P';
		break;
	case 1:
		piece_icon = 'p';
		break;
	}
}
empty::empty() : piece{} { 
	piece_icon = '-'; 
	piece_name = "empty square"; 
}
//piece colour
//int piece::piece_colour() { return 2; }
int queen::piece_colour() { return colour; }
int king::piece_colour() { return colour; }
int bishop::piece_colour() { return colour; }
int knight::piece_colour() { return colour; }
int rook::piece_colour() { return colour; }
int pawn::piece_colour() { return colour; }
int empty::piece_colour() { return 2; }//just not 0 or 1
//setting the piece icons: p/P for pawn, - for an empty space, etc.
char piece::icon() { return '-';}
char queen::icon() { return piece_icon; }
char king::icon() { return piece_icon; }
char bishop::icon() { return piece_icon; }
char knight::icon() { return piece_icon; }
char rook::icon() { return piece_icon; }
char pawn::icon() { return piece_icon; }
char empty::icon() { return piece_icon; }
//setting pieces names
//std::string piece::name() { return 0; };
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
//decreaseing the number of moves made
void piece::undo_piece_move() {};
void queen::undo_piece_move() { number_of_moves--; }
void king::undo_piece_move() { number_of_moves--; }
void bishop::undo_piece_move() { number_of_moves--; }
void knight::undo_piece_move() { number_of_moves--; }
void rook::undo_piece_move() { number_of_moves--; }
void pawn::undo_piece_move() { number_of_moves--; }
//valid move function definitions
bool piece::valid_move(std::string location, std::string destination, bool take_piece) { return 0; }
bool queen::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = abs(string_to_rank(destination) - string_to_rank(location));
	int file_move_distance = abs(string_to_file(destination) - string_to_file(location));
	if ((rank_move_distance == 0 && file_move_distance > 0 && file_move_distance <= 8) || (file_move_distance == 0 && rank_move_distance > 0 && rank_move_distance <= 8) 
		|| (rank_move_distance == file_move_distance && rank_move_distance > 0 && file_move_distance > 0 && rank_move_distance <= 8 && file_move_distance <= 8)) {
		//queen can move in straight lines and diagonals 
		return 1;
	}
	else { return 0; }
}
bool king::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = abs(string_to_rank(destination) - string_to_rank(location));
	int file_move_distance = abs(string_to_file(destination) - string_to_file(location));
	//can move only one square but in any direction unless castling
	if ((rank_move_distance == 1 && file_move_distance == 1)|| (rank_move_distance == 1 && file_move_distance == 0)
		||(rank_move_distance == 0 && file_move_distance == 1)) {
		return 1;
	}
	else if (rank_move_distance == 2 && file_move_distance == 0 && number_of_moves == 0) {
		return 1;
	}
	else { return 0; }
}
bool bishop::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = abs(string_to_rank(destination) - string_to_rank(location));
	int file_move_distance = abs(string_to_file(destination) - string_to_file(location));
	//can move only diagonals
	if (rank_move_distance == file_move_distance && rank_move_distance > 0 && file_move_distance > 0) {
		return 1;
	}
	else { return 0; }
}
bool knight::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = abs(string_to_rank(destination) - string_to_rank(location));
	int file_move_distance = abs(string_to_file(destination) - string_to_file(location));
	//can move in L shapes
	if ((rank_move_distance == 2 && file_move_distance == 1)||(rank_move_distance == 1 && file_move_distance == 2)) {
		return 1;
	}
	else { return 0; }
}
bool rook::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = abs(string_to_rank(destination) - string_to_rank(location));
	int file_move_distance = abs(string_to_file(destination) - string_to_file(location));
	//can move only straight lines
	if ((rank_move_distance == 0 && file_move_distance > 0 )|| (file_move_distance == 0 && rank_move_distance > 0)) {
		return 1;
	}
	else { return 0; }
}
bool pawn::valid_move(std::string location, std::string destination, bool take_piece) {
	int rank_move_distance = string_to_rank(destination) - string_to_rank(location);
	int file_move_distance = abs(string_to_file(destination) - string_to_file(location));
	//Can move 1 square forward, 2 if its the first go. Can only take on the diagonal
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