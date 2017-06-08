#pragma once
#include <iostream>
#include <string>
#include "Singleton.h"// might move
namespace AFG_Games 
{
	class IGame
	{
	public:// <- not needed in struct
		IGame(unsigned PlayerCount = 1);
		virtual void PlayGame();
		unsigned int PlayerID()const;
		virtual void Instructions() = 0;
		virtual void DisplayGame() = 0;
		virtual std::string name()const = 0;
	protected:
		unsigned  Turn()const;
		unsigned  PlayerCount()const;
		virtual void OnEndGame();
		virtual void GameLogic() = 0;
		virtual bool Playing() = 0;
		virtual void PrintResults() = 0;
		virtual ~IGame();
	private:
		unsigned _Turn, _PlayerCount;
	};
}