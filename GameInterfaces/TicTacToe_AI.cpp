#include "TicTacToe_AI.h"

namespace AFG_Games
{
	void TicTacToe_AI::AIGameLogic()
	{
		unsigned pos = 0, weight = 0;
		for (int i = pos + 1; i < ROW * COL; ++i)
		{
			if ((Grid[i] == EMPTY && Table[Turn()][i] >= weight))
			{
				pos = i;
				weight = Table[Turn()][i];
			}
		}
		Grid[pos] = PlayerToken();
	}
	void TicTacToe_AI::GameLogic()
	{
		if(isAI())
		{ 
			AIGameLogic();
		}
		else// Human Plays Turn
		{
			TicTacToe::GameLogic();
		}
		UpdateTable();
	}
	bool TicTacToe_AI::isAI()const
	{
		return (PlayerID() == 0 && P1AI) || (PlayerID() == 1 && P2AI);
	}
	void TicTacToe_AI::setAI(bool a, bool b)
	{
		P1AI = a;
		P2AI = b;
	}
	void TicTacToe_AI::Instructions()
	{
		if (!isAI())
			TicTacToe::Instructions();
		else
		{
			std::cout << "Bot#" << PlayerID() <<" will make a move on Turn#"<<Turn()+1<<std::endl;
		}
	}
	void TicTacToe_AI::OnEndGame()
	{
		P1Wins = P2Wins = false;
		R_Choice = C_Choice = 0;
		for (int i = 0; i < ROW * COL; ++i) Grid[i] = EMPTY;
		IGame::OnEndGame();
	}
	void TicTacToe_AI::UpdateTable()
	{

	}
}