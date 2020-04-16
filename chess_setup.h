//inital setup of the board
//piece worth: pawn,1; knight,bishop,3; rook,5; queen,9;
//maybe put classes here to call in the cpp files
#ifndef CHESS_SETUP_H
#define CHESS_SETUP_H
#include "includes.h"

namespace chess{
	//piece classes
	class piece {//abstract base class
	protected:
	public:
		piece() {};//not sure if it needs to have colour put in here
		virtual ~piece() { std::cout << "destroying piece" << std::endl; }
		virtual std::string icon();
		bool captured;
		//bool static check_king(); //check if the king is in check?
		//static std::string current_position();
		//virtual std::string location();
		//location
		//typedef std::map<std::string, int> location;
		
	};
	class queen : public piece {
	private:
		double points{9};
		int colour; //either 1 or 0 (w or b)
		std::string piece_icon;
	public:
		queen(int Q_colour) : piece{} { 
			colour = Q_colour;
			if (colour == 0) {
				//uppercase for white
				piece_icon = "Q";
			}
			else {
				//lowercase for black
				piece_icon = "q";
			}
		}
		~queen() { std::cout << "destroying queen" << std::endl; }
		std::string icon();
		//location queens_location;
		//queens_location.insert(std::pair<std::string, int>("a", 1));
		//std::string location();
	};
	class king : public piece {
	private:
	int colour;
	std::string piece_icon;
	public:
		king(int K_colour) : piece{} { 
			colour = K_colour; 
			if (colour == 0) {
				//uppercase for white
				piece_icon = "K";
			}
			else {
				//lowercase for black
				piece_icon = "k";
			}
		}
		~king() { std::cout << "destroying king" << std::endl; }
		std::string icon();
	};
	class bishop : public piece {
	private:
		int colour;
		std::string piece_icon;
	public:
		bishop(int B_colour) : piece{} { 
			colour = B_colour; 
			if (colour == 0) {
				//uppercase for white
				piece_icon = "B";
			}
			else {
				//lowercase for black
				piece_icon = "b";
			}
		}
		~bishop() { std::cout << "destroying bishop" << std::endl; }
		std::string icon();
	};
	class knight : public piece {
	private:
		int colour;
		std::string piece_icon;
	public:
		knight(int K_colour) : piece{} { 
			colour = K_colour; 
			if (colour == 0) {
				//uppercase for white
				piece_icon = "N";
			}
			else {
				//lowercase for black
				piece_icon = "n";
			}
		}
		~knight() { std::cout << "destroying knight" << std::endl; }
		std::string icon();
	};
	class rook : public piece {
	private:
		int colour;
		std::string piece_icon;
	public:
		rook(int R_colour) : piece{} { 
			colour = R_colour; 
			if (colour == 0) {
				//uppercase for white
				piece_icon = "R";
			}
			else {
				//lowercase for black
				piece_icon = "r";
			}
		}
		~rook() { std::cout << "destroying rook" << std::endl; }
		std::string icon();
	};
	class pawn : public piece {
	private:
		int colour;
		std::string piece_icon;
		bool iswhite();//used to determine which direction the pawn can move in
	public:
		pawn(int p_colour) : piece{} { 
			colour = p_colour; 
			if (colour == 0) {
				//uppercase for white
				piece_icon = "P";
			}
			else {
				//lowercase for black
				piece_icon = "p";
			}
		}
		~pawn(){ std::cout << "destroying pawn" << std::endl; }
		std::string icon();
		static std::string pawn_allowed_move(int);
	};
	class empty : public piece {
	private:
		std::string piece_icon;
	public:
		empty() : piece{} { piece_icon = "-"; }
		~empty() { std::cout << "destroying empty" << std::endl; }
		std::string icon();
	};
	//class of the chess board that contains the current locations of all the pieces
	//including the captured ones
	class board {
		/*const char starting_board[8][8] =
		{
			{ 'r','n' , 'b','q' ,'k' ,'b' ,'n' ,'r' },
			{ 'p','p' , 'p','p' ,'p' ,'p' ,'p' ,'p' },
			{ '-', '-', '-', '-', '-', '-', '-', '-'},
			{ '-', '-', '-', '-', '-', '-', '-', '-'},
			{ '-', '-', '-', '-', '-', '-', '-', '-'},
			{ '-', '-', '-', '-', '-', '-', '-', '-'},
			{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
			{ 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
		};*/
		//tracks position of all the pieces
	private:
		//2d vector to have pointers to all the pieces on the board
		std::vector<std::vector<piece*>> current_board;
	public:
		board() {
			//set up the starting board
			current_board.resize(8, std::vector<piece*>(8));
			//piece pieces = new piece[64];
			//current_board[0].push_back(new queen(0));
			//white pieces
			try {
				current_board.at(0).at(0) = new rook(1);
				current_board.at(0).at(1) = new knight(1);
				current_board.at(0).at(2) = new bishop(1);
				current_board.at(0).at(3) = new queen(1);
				current_board.at(0).at(4) = new king(1);
				current_board.at(0).at(5) = new bishop(1);
				current_board.at(0).at(6) = new knight(1);
				current_board.at(0).at(7) = new rook(1);
				for (int i{}; i < 8; i++) {
					current_board.at(1).at(i) = new pawn(1);
				}
				for (int j{2}; j < 6; j++) {
					for (int i{}; i < 8; i++) {
						current_board.at(j).at(i) = new empty();
					}
				}
				for (int i{}; i < 8; i++) {
					current_board.at(6).at(i) = new pawn(0);
				}
				current_board.at(7).at(0) = new rook(0);
				current_board.at(7).at(1) = new knight(0);
				current_board.at(7).at(2) = new bishop(0);
				current_board.at(7).at(3) = new queen(0);
				current_board.at(7).at(4) = new king(0);
				current_board.at(7).at(5) = new bishop(0);
				current_board.at(7).at(6) = new knight(0);
				current_board.at(7).at(7) = new rook(0);
			}
			catch (std::out_of_range e) {
				std::cout << "well fuck" << std::endl;
			}
			//current_board.clear();
		};
		~board() { delete &current_board; std::cout << "destroying board" << std::endl; }
		std::vector<std::unique_ptr<piece>> taken_pieces; //keep track of captured pieces
		std::vector<std::string> list_of_moves_made; //keep track of all the moves in san.
		void update_board(std::string move); //update and display board
		void display_board();
		void user_input();
		void valid_move();
		//checks if move is valid that sort of thing
		//try and except / catch here
		//chnages pieces location
		//functions to do this
		//void movepiece()
		//void takepiece()
		//void castling()
		//void promotion() making a pawn a queen, knight, rook or bishop
		//void en_passant() //fucking cheating is what it is
	};

	class game {
		game() {};
		~game() {};
		//pull all the functions together in a coherent set up
		//maybe see if need

		//checks if move is valid that sort of thing
		//try and except / catch here
		//chnages pieces location
		//functions to do this
		//void movepiece()
		//void takepiece()
		//void castling()
		//void promotion() making a pawn a queen, knight, rook or bishop
		//void en_passant() //fucking cheating is what it is
	};
}
#endif