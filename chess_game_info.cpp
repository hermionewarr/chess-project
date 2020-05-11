//functions for chess_game
#include "includes.h"
#include "chess_game_info.h"

namespace chess_game_info_ns {
	game_info chess_info;
	void game_info::Rules() {
		//option to see the rules and info
		std::string yn;
		std::cout << "Would you like to see the infomation for this chess game? (y/n)" << std::endl;
		std::cin >> yn;
		if (yn == "y" || yn == "Y" || yn == "yes") {
			std::cout << "This is a representation of the board.\n" << std::endl;
			std::cout << "     A B C D E F G H" << std::endl;
			std::cout << "    -----------------" << std::endl;
			std::cout << " 8 | r n b q k b n r | 8" << std::endl;
			std::cout << " 7 | p p p p p p p p | 7" << std::endl;
			std::cout << " 6 | - - - - - - - - | 6" << std::endl;
			std::cout << " 5 | - - - - - - - - | 5" << std::endl;
			std::cout << " 4 | - - - - - - - - | 4" << std::endl;
			std::cout << " 3 | - - - - - - - - | 3" << std::endl;
			std::cout << " 2 | P P P P P P P P | 2" << std::endl;
			std::cout << " 1 | R N B Q K B N R | 1" << std::endl;
			std::cout << "    -----------------" << std::endl;
			std::cout << "     A B C D E F G H" << std::endl;
			std::cout << "\nThe white pieces are represented by capitals and the black by lowercase." << std::endl;
			std::cout << "The dashed lines are empty spaces on the board." << std::endl;
			std::cout << "The Pieces : P: Pawn, R : Rook or Castle, N : Knight, B : Bishop, Q : Queen, K : King." << std::endl;
			std::cout << "The rules of chess can be found here : https://en.wikipedia.org/wiki/Rules_of_chess\n" << std::endl;
			std::cout << "This game uses a version of algebraic notation: for example a move of a black pawn from E7 to empty square E5, would " << std::endl;
			std::cout << "be displayed as p:e7->-e5. A move to an empty is denoted as ->-, taking a piece ->T, castling ->C and pawn promotion ->Q." << std::endl;
			std::cout << "This is how the game will be displayed at the end, other than that you dont need to worry about it!" << std::endl;
			std::cout << "\nThe Save game<S> option alows you to save a game and replay or come back to it later." << std::endl;
			std::cout << "\nThe Load game<L> option allows you to play or rewatch a saved game. There are several saved games already which can be veiwed." << std::endl;
			std::cout << "DeepBlue_Kasparov_G1, checkmate_eg, castling_setup are the names of the presaved games." << std::endl;
			std::cout << "DeepBlue_Kasparov_G1 is a replay of the first game where a computer program defeated a world champion in a classical game under tournament regulations" << std::endl;
			std::cout << "Kasparov resigned before checkmate occured so you can finish the game off." << std::endl;
			std::cout << "checkmate_eg includes a pawn promotion and is a complete game to replay, castling_setup drops you into a game where you can castle and carry on playing." << std::endl;
			std::cout << "\nReady to play? (y/n)" << std::endl;
			std::string start_play;
			std::cin >> start_play;
			while (start_play != "n" && start_play != "y") {				
				std::cin.clear();
				std::cout << "Please enter y or n: ";
				std::cin >> start_play;
			}
			if (start_play == "y") {
				std::cout << "Get ready! " << std::endl;
				return;
			}
			else if (start_play == "n"){
				exit(0);
			}
		}
		else if (yn == "n" || yn == "N" || yn == "no") {
			std::cout << "Ok lets play!" << std::endl;
			return;
		}
		else {
			std::cout << "Please enter y or n: " << std::endl;
			std::cin.clear();
			Rules();
		}
	}
	void game_info::starting_display() {
		//this looks weird but dont touch!
		std::system("cls");
		std::cout << "		  ============================================" << std::endl;
		std::cout << "		      _____  _    _  ______   _____   _____ " << std::endl;
		std::cout << "		     / ____|| |  | ||  ____| / ____/ / ____| " << std::endl;
		std::cout << "		    | |     | |__| || |___  | (___  | (___  " << std::endl;
		std::cout << "		    | |     |  __  ||  ___|  \\___ \\  \\___ \\ " << std::endl;//have to put two \\ to get one
		std::cout << "		    | |____ | |  | || |____  ____) | ____) | " << std::endl;
		std::cout << "		     \\_____||_|  |_||______||_____/ |_____/ " << std::endl;
		std::cout << "\n		  ============================================\n" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);//pink
		std::cout << "	           ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 80);//purple
		std::cout << "           ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16);//blue
		std::cout << "           ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 32);//green
		std::cout << "           ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);//yellow
		std::cout << "           ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64);//red
		std::cout << "           \n" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
		std::cout << "\t\t\t   Student ID: 10134857 \n" << std::endl;
	}
	void game_info::checkmate_display() {
		std::system("cls");
		std::cout << "    ======================================================================================" << std::endl;
		std::cout << "        _____  _    _  ______   _____  _   _   __    __    ____   _________  ______   _   " << std::endl;
		std::cout << "       / ____|| |  | ||  ____| / ____|| | / / |  \\  /  |  / __ \\ |___   ___||  ____| | |  " << std::endl;
		std::cout << "      | |     | |__| || |___  | |     | |/ /  |   \\/   | / /__\\ \\    | |    | |___   | | " << std::endl;
		std::cout << "      | |     |  __  ||  ___| | |     |   (   | |\\__/| ||  ____  |   | |    |  ___|  |_| " << std::endl;
		std::cout << "      | |____ | |  | || |____ | |____ | |\\ \\  | |    | || |    | |   | |    | |____   _  " << std::endl;
		std::cout << "       \\_____||_|  |_||______| \\_____||_| \\_\\ |_|    |_||_|    |_|   |_|    |______| |_| " << std::endl;
		std::cout << "\n    ======================================================================================\n" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);//pink
		std::cout << "                ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 80);//purple
		std::cout << "                ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16);//blue
		std::cout << "                ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 32);//green
		std::cout << "                ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);//yellow
		std::cout << "                ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64);//red
		std::cout << "                \n" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 33, 12 });
	}
}