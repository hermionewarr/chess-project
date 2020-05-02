//inital setup of the board
//piece worth: pawn,1; knight,bishop,3; rook,5; queen,9;
//maybe put classes here to call in the cpp files
#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H
#include "includes.h"


//piece classes
class piece {//abstract base class
protected:
public:
	virtual ~piece() { std::cout << "destroying piece" << std::endl; }
	virtual char icon();
	virtual std::string name();
	virtual int number_of_moves_made();
	virtual void piece_move();
	//bool captured{false};
	virtual std::string rank_file_location(int row, int col);
	virtual int string_to_rank_int(std::string location);
	virtual int string_to_file_int(std::string location);
	virtual int piece_colour();
	virtual bool valid_move(std::string location, std::string destination, bool take_piece);
	//bool static check_king(); //check if the king is in check?
	//static std::string current_position();
	//virtual std::string location();
	//location
	//typedef std::map<std::string, int> location;
	
};
class queen : public piece {
private:
	double points{9};
	int colour{}; //either 1 or 0 (w or b)
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	queen(int Q_colour) : piece{} { 
		colour = Q_colour;
		piece_name = "Queen";
		if (colour == 0) {
			//uppercase for white
			piece_icon = 'Q';
		}
		else {
			//lowercase for black
			piece_icon = 'q';
		}
	}
	~queen() { std::cout << "destroying queen" << std::endl; }
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
	//location queens_location;
	//queens_location.insert(std::pair<std::string, int>("a", 1));
	//std::string location();
};
class king : public piece {
private:
	int colour;
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	king(int K_colour) : piece{} { 
		colour = K_colour; 
		piece_name = "King";
		if (colour == 0) {
			//uppercase for white
			piece_icon = 'K';
		}
		else {
			//lowercase for black
			piece_icon = 'k';
		}
	}
	~king() { std::cout << "destroying king" << std::endl; }
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class bishop : public piece {
private:
	int colour;
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	bishop(int B_colour) : piece{} { 
		colour = B_colour; 
		piece_name = "Bishop";
		if (colour == 0) {
			//uppercase for white
			piece_icon = 'B';
		}
		else {
			//lowercase for black
			piece_icon = 'b';
		}
	}
	~bishop() { std::cout << "destroying bishop" << std::endl; }
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class knight : public piece {
private:
	int colour;
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	knight(int K_colour) : piece{} { 
		colour = K_colour; 
		piece_name = "Knight";
		if (colour == 0) {
			//uppercase for white
			piece_icon = 'N';
		}
		else {
			//lowercase for black
			piece_icon = 'n';
		}
	}
	~knight() { std::cout << "destroying knight" << std::endl; }
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class rook : public piece {
private:
	int colour;
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	rook(int R_colour) : piece{} { 
		colour = R_colour; 
		piece_name = "Rook";
		if (colour == 0) {
			//uppercase for white
			piece_icon = 'R';
		}
		else {
			//lowercase for black
			piece_icon = 'r';
		}
	}
	~rook() { std::cout << "destroying rook" << std::endl; }
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class pawn : public piece {
private:
	int colour;
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;

public:
	pawn(int p_colour) : piece{} { 
		colour = p_colour; 
		piece_name = "Pawn";
		if (colour == 0) {
			//uppercase for white
			piece_icon = 'P';
		}
		else {
			//lowercase for black
			piece_icon = 'p';
		}
	}
	~pawn(){ std::cout << "destroying pawn" << std::endl; }
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class empty : public piece {
private:
	char piece_icon;
	std::string piece_name;
public:
	empty() : piece{} { piece_icon = '-'; piece_name = "empty square"; }
	~empty() { std::cout << "destroying empty" << std::endl; }
	char icon();
	std::string name();
	int piece_colour();
};

#endif