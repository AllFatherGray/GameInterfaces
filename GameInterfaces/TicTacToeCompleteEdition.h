#pragma once
#include "TicTacToe_AI.h"
namespace AFG_Games 
{
	class TicTacToeCompleteEdition : public IGame, public Singleton<TicTacToeCompleteEdition>//: public TicTacToe_AI, public TicTacToe
	{
		void PlayGame()
		{
			unsigned response;
			std::cout << "Enter 0 - AIBattle" << std::endl;
			std::cout << "Enter 1 - P1 vs AI" << std::endl;
			std::cout << "Enter 2 - P1 vs P2" << std::endl;
			std::cin >> response;
			switch (response)
			{
				case 0:
				{
					TicTacToe_AI::Instance().setAI(true, true);
					return TicTacToe_AI::Instance().PlayGame();
				}
				case 1:
				{
					std::cout << "Enter 0 - To go 1st" << std::endl;
					std::cout << "Enter 1 - To go 2nd" << std::endl;
					std::cout << "Enter 2 - Random" << std::endl;
					std::cin >> response;
					response %= 3;
					response = response == 2 ? rand() % 2 : response;
					TicTacToe_AI::Instance().setAI(response == 1, response == 0);
					return TicTacToe_AI::Instance().PlayGame();
				}
				case 2:
				{
					TicTacToe_AI::Instance().setAI(false, false);
					return TicTacToe::Instance().PlayGame();
				}
			};
		}
		void Instructions() {}
		void DisplayGame() {}
		std::string name()const { return "TicTacToe - Complete Edition"; }
		void GameLogic() {}
		bool Playing() { return true; }
		void PrintResults() {}
	};
}