#pragma once
#include <random>
#include <iostream>
#include <iomanip>
#include <string>
#include "Singleton.h"// might move
namespace AFG_Games 
{
	struct GameAssetArgs;
	class IGame
	{
	public:// <- not needed in struct
		IGame(unsigned PlayerCount = 1);
		virtual void PlayGame();
		unsigned int PlayerID()const;
		virtual void Instructions() = 0;
		virtual void DisplayGame() = 0;
		virtual std::string name()const = 0;
		static GameAssetArgs& Assets(int argc = 0, char *argv[] = NULL);
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
	struct GameAssetArgs
	{
		GameAssetArgs(int argc, char *argv[])
		{
			this->argc = argc;
			this->argv = argv;
		}
		std::string GetAssetName(AFG_Games::IGame* g, std::string valid)
		{
			if (Arguments() != NULL)
			{
				for (int i = 0; i < Size(); ++i)
				{
					if (g->name() + valid == Arguments()[i])
					{
						return Arguments()[i];
					}
				}
			}
			return " ";
		}
		int Size()const
		{
			return argc;
		}
		char** Arguments()const
		{
			return argv;
		}
		void Print()const
		{
			std::cout << "Number of Arguments :" << Size() << std::endl;
			for (int i = 0; i < Size(); ++i)
			{
				std::cout << "Asset #"<< i << " "<< Arguments()[i] << std::endl;
			}
		}
	private:
		int argc;
		char ** argv;
	};
}