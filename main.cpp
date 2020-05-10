//Final project: Chess boardgame
//Student ID: 10134857
//Made: 05/2020

#include "includes.h"
#include "chess_pieces.h"
#include "Chess_board.h"
#include "chess_game_info.h"

int main()
{
	bool play_again = true;
	while (play_again == true) {
		//Chess_game namespace
		chess_game_info_ns::game_info chess_info;
		chess_info.starting_display();
		//option to see the rules and infomation
		chess_info.Rules();
		//start the game
		chess_info.starting_display();
		board chess_game;
		while (!chess_game.game_over) {
			chess_game.user_input();
		}
		chess_info.checkmate_display();
		std::cout << "\t "<< chess_game.return_current_turn() << " has won!\n" << std::endl;
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
			std::cout << "Do you want to play again? (y/n): ";
			std::cin >> again;
		}
		if (again == "y") { play_again = true; std::system("cls"); }
		else { 
			play_again = false; 
			std::cout << "\nSee you next time!" << std::endl;
		}
	}
	return 0;
}