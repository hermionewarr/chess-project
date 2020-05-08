//Hermione Warr - final project: Chess boardgame
//Made: 05/2020

#include "includes.h"
#include "chess_pieces.h"
#include "Chess_board.h"
#include "chess_game.h"

int main()
{
	/*#include <Windows.h>
	int k{};
	for (k = 1; k < 255; k++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
		std::cout << k << "Colours!" << std::endl;
	}*/
	bool play_again = true;
	while (play_again == true) {
		std::cout << "\n\t    Chess Game" << std::endl;
		std::cout << "\t- by Hermione Warr \n" << std::endl;
		//Chess_game namespace
		Chess_game::Game game;
		//option to see the rules
		game.Rules();
		//start the game
		game.starting_display();
		board chess_game;
		while (!chess_game.game_over) {
			chess_game.user_input();
		}
		game.checkmate_display();
		std::cout << "\t "<< chess_game.return_current_turn() << " has won!" << std::endl;
		std::string show_game;
		std::cout << "Show the moves of the game? (y/n): ";
		std::cin >> show_game;
		while (show_game != "y" && show_game != "n") {
			std::cin.clear();
			std::cout << "Please answer (y/n): ";
		}
		if (show_game == "y" || show_game == "Y") {
			chess_game.show_game();
		}
		//play again?
		std::string again;
		while (again != "y" && again != "n") {
			std::cin.clear();
			std::cout << "Do you want to play again?(y/n)" << std::endl;
			std::cin >> again;
		}
		if (again == "y") { play_again = true; std::system("cls"); }
		else { 
			play_again = false; 
			std::cout << "See you next time!" << std::endl;
		}
	}
	return 0;
}