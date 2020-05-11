//The chess board class
//Contains the current locations of all the pieces and the functions to move them
//displays the board

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include "includes.h"
#include "chess_pieces.h"

class board {
private:
	//array of shared pointers to all the pieces on the board
	std::vector < std::shared_ptr<piece>> current_board; 
	std::vector<std::shared_ptr<piece>> taken_pieces;
	std::vector<std::string> list_of_moves_made; 
	std::vector<std::string> help(std::string location); //show all allowed moves for a piece.
	int current_turn{ 0 }; //0 for white and 1 for black;
public:
	board();
	~board();
	bool game_in_play = false;
	bool game_over = false;
	//Return position in vector of element (m,n)
	int index(size_t m, size_t n) const;
	std::shared_ptr<piece> operator[](int index) const;
	//changing entered locations to index entries for the board array and back
	int string_to_file(std::string location) const;
	int string_to_rank(std::string location) const;
	int string_to_index(std::string location) const;
	std::string string_coordinate(const int vector_index) const;
	//the functions involved with moving a piece
	void move_input();
	bool move(std::string location, std::string destination);
	//functions to validify a move
	bool is_path_clear(std::string piece_location, std::string piece_destination);
	bool castling_possible(std::string king_location, std::string king_destination);
	bool king_in_check();
	void undo_move();
	bool checkmate();
	//move functions to change piece location
	void swap_piece(std::string location, std::string destination, bool undo_move);
	void take_piece(std::string location, std::string destination);
	void castling(std::string location, std::string destination);
	void promotion(std::string location, std::string destination);
	void en_passant(std::string location, std::string destination);
	//functions to display the board
	void display_board();
	void whose_turn();
	std::string return_current_turn();
	std::string winner();
	void cool_move();
	//user_input is the entrance point to the game and calls the functions to play
	void user_input();
	int move_number();
	//function declarations to allow games to be saved as txt files and loaded into the boards
	void save_game();
	void load_game();
	void show_game();
};



#endif // !CHESS_BOARD_H



