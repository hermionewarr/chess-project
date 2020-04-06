//inital setup of the board
//maybe put classes here to call in the cpp files
#pragma once
#include "includes.h"

namespace chess{
	
	//piece classes
	class piece {//abstract base class
	protected:
		std::string colour{};
		std::string name{};
		int points{};
	public:
		std::string black, white;
		piece(std::string piece_colour) { colour = piece_colour; }//not sure if it needs to have colour put in here
		virtual ~piece() { std::cout << "destroying piece" << std::endl; }
		bool captured;
		//location
		pair<char, double> location;
	};
	class black_piece : public piece {
	protected:
	public:
		black_piece() : piece{ black } {};
		virtual ~black_piece() { std::cout << "destroying black piece" << std::endl; }
	};
	class white_piece : public piece {
	protected:
		//moves first
	public:
		white_piece() : piece{ white } {};
		virtual~white_piece() { std::cout << "destroying white piece" << std::endl; }
	};
	class queen : public black_piece {
	protected:
		double points{9};
	public:
		queen() : black_piece{} {};
		~queen() { std::cout << "destroying queen" << std::endl; }
	};
	class empty : public piece {

	};
	//class of the chess board that contains the current locations of all the pieces
	//including the captured ones
	class board {
		//tracks position of all the pieces
	private:
		//2d vector to have pointers to all the pieces on the board
		std::vector<std::vector<std::unique_ptr<piece*>>> current_board;
	public:
		board() {};
		~board() { std::cout << "destroying board" << std::endl; }
	};
	class player {
		//abstract has derived class for 2 humans or 1 human and one computer player.
	};
	class game {
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