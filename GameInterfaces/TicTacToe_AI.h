#pragma once
#include "TicTacToe.h"
#include "IWeightTable.h"
namespace AFG_Games
{
	class TicTacToe_AI : public TicTacToe, public IWeightTable<9, 3, 3>, public Singleton<TicTacToe_AI>
	{
	    virtual void OnEndGame();
		void AIGameLogic();
		virtual void GameLogic();
		bool isAI()const;
		void UpdateTable();
		bool P1AI, P2AI;
		void Instructions();
		
	public:
		void setAI(bool a, bool b);
		static TicTacToe_AI& Instance()
		{
			return Singleton<TicTacToe_AI>::Instance();
		}
	};
}