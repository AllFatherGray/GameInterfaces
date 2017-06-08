#pragma once
#include "IGame.h"
#include "TicTacToeCompleteEdition.h"
#include <vector>
namespace AFG_Games 
{
	class GameLibrary : public Singleton<GameLibrary>
	{
	public:
		// Call this in main()
		static void OpenMenu();
		static unsigned NumberOfGames();
	private:
		// Add Games Here
		GameLibrary();
		~GameLibrary();
		std::vector<IGame*> Index_of_Games;
	};
}