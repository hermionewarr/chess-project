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
	//array of chared pointers to all the pieces on the board
	std::vector < std::shared_ptr<piece>> current_board; 
	std::vector<std::shared_ptr<piece>> taken_pieces; //keep track of captured pieces
	std::vector<std::string> list_of_moves_made; //keep track of all the moves
	std::vector<std::string> help(std::string location); //show all allowed moves for a piece.
	int current_turn{ 0 }; //0 for white and 1 for black;
	//int number_of_moves{};
public:
	board();
	~board() { taken_pieces.clear(); list_of_moves_made.clear(); current_turn = 0; current_board.clear(); }
	bool game_in_play = false;
	bool game_over = false;
	//Return position in array of element (m,n)
	int index(size_t m, size_t n) const;
	//changing entered locations to index entries for the board array and back
	int string_to_file(std::string location);
	int string_to_rank(std::string location);
	std::string rank_file_string_coordinate(int vector_index);
	//the functions involved with moving a piece
	void move_input();
	bool move(std::string location, std::string destination);
	//functions to validify a move
	bool is_path_clear(std::string piece_location, std::string piece_destination);
	void whose_turn();
	std::string return_current_turn();
	bool castling_possible(std::string king_location, std::string king_destination);
	bool king_in_check();
	bool checkmate();
	void undo_move();
	//functions to display the board
	void display_board();
	void cool_move();
	//user_input is the entrance point to the game and calls the functions to play
	void user_input();
	int move_number();
	void save_game();
	void load_game();
	void show_game();
	//move functions to change piece location
	void swap_piece(std::string location, std::string destination, bool undo_move);
	void take_piece(std::string location, std::string destination);
	void castling(std::string location, std::string destination);
	void promotion(std::string location, std::string destination); //making a pawn a queen, knight, rook or bishop
	//void en_passant() //fucking cheating is what it is
	//std::string board_location(int vector_index);
	typedef std::map<int, std::string> location_in_board_vector;
	void search_board_vector(location_in_board_vector& the_board, int vector_index);
};



#endif // !CHESS_BOARD_H



