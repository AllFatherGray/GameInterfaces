#include "GameLibrary.h"
namespace AFG_Games
{
	void  GameLibrary::OpenMenu()
	{
		char response;
		IGame* CurrentGame;
		do 
		{
			std::cout << "Games in Library :" << std::endl;
			std::cout << "Enter the ID of the Game you wish to play :" << std::endl;
			for (unsigned i = 0; i < NumberOfGames(); ++i)
			{
				std::cout << "[" << i << "] - " << Instance().Index_of_Games[i]->name() << std::endl;
			}
			unsigned int choice;
			std::cin >> choice;
			CurrentGame = Instance().Index_of_Games[choice % NumberOfGames()];
			std::cout << "Loading " << CurrentGame->name()<<"...." << std::endl << std::endl;
			CurrentGame->PlayGame();
			std::cout << "Choose another game? Y/N : ";
			std::cin >> response;
		} while (toupper(response) == 'Y');
	    std::cout << "Thanks for playing!"<< std::endl;
	}
	unsigned GameLibrary::NumberOfGames()
	{
		return Instance().Index_of_Games.size();
	}
	GameLibrary::GameLibrary()
	{
		Index_of_Games = { &TicTacToeCompleteEdition::Instance() };
	}
	GameLibrary::~GameLibrary()
	{
		// delete vector?
	}
}