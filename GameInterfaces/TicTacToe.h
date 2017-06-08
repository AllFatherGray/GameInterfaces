#pragma once
#include "IGame.h"
namespace AFG_Games {
	// Implementation of Game interface
	class TicTacToe : public IGame, public Singleton<TicTacToe>
	{
	public:
		TicTacToe();
		void Instructions();
		void DisplayGame();
	protected:
		bool P1Wins, P2Wins;
		// Size constants
		static const unsigned ROW = 3, COL = 3;
		// Legend for Players
		static const char EMPTY = '-', P1 = 'X', P2 = 'O';
		// Row and Col Choices
		unsigned R_Choice, C_Choice;
		// Grid for Game
		char Grid[ROW * COL];
		bool HasWon(char token)const;
		bool ValidToken(char token, unsigned row = 0, unsigned col = 0)const;
		// Returns true if a Tile On the Board is Still Vacant
		bool HasSpace()const;
		//Returns the Token of Current Player
		char PlayerToken()const;
		virtual std::string name()const;
		virtual void GameLogic();
		virtual bool Playing();
		virtual void PrintResults();
		virtual void OnEndGame();
	};
}