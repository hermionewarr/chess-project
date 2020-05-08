//polymorphic class model for the pieces
//piece worth: pawn,1; knight,bishop,3; rook,5; queen,9;

#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H
#include "includes.h"

//abstract base class
class piece {
protected:
public:
	virtual ~piece() {};
	virtual char icon();
	virtual std::string name() = 0;
	virtual int number_of_moves_made();
	virtual void piece_move();
	virtual void undo_piece_move();
	virtual int piece_colour() = 0;
	virtual bool valid_move(std::string location, std::string destination, bool take_piece);	
};
//derived classes
class queen : public piece {
private:
	int colour{}; //either 1 or 0 (black or white respectively)
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	queen(int Q_colour);
	~queen() {};
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	void undo_piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class king : public piece {
private:
	int colour;
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	king(int K_colour);
	~king() {};
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	void undo_piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class bishop : public piece {
private:
	int colour;
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	bishop(int B_colour);
	~bishop() {};
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	void undo_piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class knight : public piece {
private:
	int colour;
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	knight(int K_colour);
	~knight() {};
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	void undo_piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class rook : public piece {
private:
	int colour;
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	rook(int R_colour);
	~rook() {};
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	void undo_piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class pawn : public piece {
private:
	int colour;
	int number_of_moves{};
	char piece_icon;
	std::string piece_name;
public:
	pawn(int p_colour);
	~pawn() {};
	char icon();
	std::string name();
	int piece_colour();
	int number_of_moves_made();
	void piece_move();
	void undo_piece_move();
	bool valid_move(std::string location, std::string destination, bool take_piece);
};
class empty : public piece {
private:
	char piece_icon;
	std::string piece_name;
public:
	empty();
	~empty() {};
	char icon();
	std::string name();
	int piece_colour();
};

#endif