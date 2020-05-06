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
	//piece **current_board = new piece*[64];
	std::vector < std::shared_ptr<piece>> current_board; //std::shared_ptr<piece> test = std::make_shared<pawn>(8, colour::Black, 0);
	int current_turn{ 0 }; //0 for white and 1 for black;
	//int number_of_moves{};
public:
	board();
	~board() { delete& current_board; std::cout << "destroying board" << std::endl; }
	std::vector<std::shared_ptr<piece>> taken_pieces; //keep track of captured pieces
	std::vector<std::string> list_of_moves_made; //keep track of all the moves in san.
	// Return position in array of element (m,n)
	int index(size_t m, size_t n) const;
	//std::string board_location(int vector_index);
	typedef std::map<int, std::string> location_in_board_vector;
	void search_board_vector(location_in_board_vector& the_board, int vector_index);
	void move();
	void undo_move();
	void display_board();
	void user_input();
	void whose_turn();
	std::string return_current_turn();
	std::vector<std::string> help(std::string location);
	int move_number();
	bool is_path_clear(std::string piece_location, std::string piece_destination);
	bool king_in_check();
	bool checkmate();
	bool game_over = false;
	//changing entered locations to index entries for the board array
	int string_to_file(std::string location);
	int string_to_rank(std::string location);
	std::string rank_file_string_coordinate(int vector_index);
	//checks if move is valid that sort of thing
	//functions to change piece location
	void swap_piece(std::string location, std::string destination, bool undo_move);
	void take_piece(std::string location, std::string destination);
	void castling(std::string location, std::string destination);
	void promotion(std::string location, std::string destination); //making a pawn a queen, knight, rook or bishop
	//void en_passant() //fucking cheating is what it is
};



#endif // !CHESS_BOARD_H



