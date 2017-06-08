#include "IGame.h"
namespace AFG_Games
{
	IGame::IGame(unsigned PlayerCount) { _Turn = 0; _PlayerCount = PlayerCount > 0 ? PlayerCount : 1;  }
	IGame::~IGame() { }
	void IGame::PlayGame()
	{
		if (Playing())
		{			
			DisplayGame();
			Instructions();
			GameLogic();
			++_Turn;
		}
		else
		{
			PrintResults();
			_Turn = 0;
			return OnEndGame();
		}
		return PlayGame();
	}
	unsigned  IGame::Turn()const
	{
		return _Turn;
	}
	unsigned  IGame::PlayerCount()const
	{
		return _PlayerCount;
	}
	unsigned int IGame::PlayerID()const
	{
		return _Turn % _PlayerCount;
	}
	void IGame::OnEndGame()
	{
		std::cout << "Play again? Y/N : ";
		char response;
		std::cin >> response;
		if (toupper(response) == 'Y') return PlayGame();
		std::cout << "Thanks for playing " << name() <<"!"<<std::endl;
	}
}