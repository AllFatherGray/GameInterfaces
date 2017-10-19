#pragma once
#include "IGame.h"
#include "TicTacToeCompleteEdition.h"
#include "BattleShipGame.h"
#include <vector>
namespace AFG_Games 
{
	class GameLibrary : public Singleton<GameLibrary>
	{
	public:
		// Call this in main()
		static void OpenMenu(int argc, char *argv[]);
		static unsigned NumberOfGames();
		GameLibrary();
		~GameLibrary();
	private:
		// Add Games Here
		
		std::vector<IGame*> Index_of_Games;
	};
}