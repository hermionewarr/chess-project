//contains the chess board class
//which contains the current locations of all the pieces
//including the captured ones
#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include "includes.h"
#include "chess_pieces.h"

//namespace chess_board {}

class board {
private:
	//array of pointers to all the pieces on the board
	piece **current_board = new piece*[64];
	int current_turn{ 0 }; //0 for white and 1 for black;
	int number_of_moves{};
public:
	board();
	~board() { delete& current_board; std::cout << "destroying board" << std::endl; }
	std::vector<piece*> taken_pieces; //keep track of captured pieces
	std::vector<std::string> list_of_moves_made; //keep track of all the moves in san.
	//to undo moves
	std::vector<std::string> location_history;
	std::vector<std::string> destination_history;
	std::vector<std::string> move_type; //ie swap, take ect.
	// Return position in array of element (m,n)
	int index(size_t m, size_t n) const;
	//piece* operator()(size_t m, size_t n) const;
	board& operator=(board&&) noexcept; //move assignment op
	void move();
	void display_board();
	void user_input();
	void valid_move();
	void whose_turn();
	int move_number();
	int king_in_check();
	bool checkmate();
	//changing entered locations to index entries for the board array
	//std::string rank_file_location(int row, int col);
	int string_to_file(std::string location);
	int string_to_rank(std::string location);
	//checks if move is valid that sort of thing
	//try and except / catch here
	//changes pieces location
	//functions to do this
	void swap_piece(std::string location, std::string destination);
	void take_piece(std::string location, std::string destination);
	void castling(std::string location, std::string destination);
	void promotion(std::string location, std::string destination); //making a pawn a queen, knight, rook or bishop
	//void en_passant() //fucking cheating is what it is
};



#endif // !CHESS_BOARD_H



