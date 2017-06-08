#include "TicTacToe.h"
namespace AFG_Games 
{	
		TicTacToe::TicTacToe() : IGame(2) 
		{
			R_Choice = C_Choice = 0;
			for (int i = 0; i < ROW * COL; ++i) Grid[i] = EMPTY;
		}
		std::string TicTacToe::name()const
		{
			return "TicTacToe";
		}
		void TicTacToe::Instructions()
		{
			std::cout <<"Turn#"<<Turn()+1 <<".Enter the Row and Col as Integers Seperated by Spaces : ";
		}
		bool TicTacToe::Playing()
		{
			P1Wins = HasWon(P1);
			P2Wins = HasWon(P2);
			return (P1Wins == P2Wins) && HasSpace();
		}
		bool TicTacToe::HasWon(char token)const
		{
			for (int r = 0; r < ROW; ++r)
			{
				for (int c = 0; c < ROW; ++c)
				{
					if (ValidToken(token, r, c))
					{
						if ((ValidToken(token, r + 1, c) && ValidToken(token, r - 1, c)) || (ValidToken(token, r, c + 1) && ValidToken(token, r, c - 1)))
						{
							return true;
						}
						else if ((ValidToken(token, r + 1, c + 1) && ValidToken(token, r - 1, c - 1)) || (ValidToken(token, r - 1, c + 1) && ValidToken(token, r + 1, c - 1)))
						{
							return true;
						}
					}
				}
			}
			return false;
		}
		bool TicTacToe::ValidToken(char token, unsigned row, unsigned col)const
		{
			return row < ROW && col < COL && Grid[(ROW * row) + col] == token;
		}
		// Returns true if a Tile On the Board is Still Vacant
		bool TicTacToe::HasSpace()const
		{
			for (int i = 0; i < ROW * COL; ++i) if (Grid[i] == EMPTY) return true;
			return false;
		}
		//Returns the Token of Current Player
		char TicTacToe::PlayerToken()const { return Turn() % 2 == 0 ? P1 : P2; }
		void TicTacToe::GameLogic()
		{
			std::cin >> R_Choice;
			std::cin >> C_Choice;
			while (Grid[(ROW * (R_Choice % ROW)) + (C_Choice % COL)] != EMPTY)
			{
				std::cout << "Sorry... PLease Pick A Vacant Tile." << std::endl;
				Instructions();
				std::cin >> R_Choice;
				std::cin >> C_Choice;
			}
			Grid[(ROW * (R_Choice % ROW)) + (C_Choice % COL)] = PlayerToken();
		}
		void TicTacToe::PrintResults()
		{
			DisplayGame();
			if (P1Wins)
			{
				std::cout << "Player 1 Wins!" << std::endl;
			}
			else if (P2Wins)
			{
				std::cout << "Player 2 Wins!" << std::endl;
			}
			else
			{
				std::cout << "Draw!" << std::endl;
			}
		}
		void TicTacToe::DisplayGame()
		{
			for (int r = 0; r < ROW; ++r)
			{
				for (int c = 0; c < ROW; ++c)
				{
					std::cout << Grid[(ROW * r) + c] << "	";
				}
				std::cout << std::endl;
				std::cout << std::endl;
			}
		}
		void TicTacToe::OnEndGame()
		{
			P1Wins = P2Wins = false;
			R_Choice = C_Choice = 0;
			for (int i = 0; i < ROW * COL; ++i) Grid[i] = EMPTY;
			IGame::OnEndGame();
		}
}