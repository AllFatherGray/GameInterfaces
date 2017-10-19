#pragma once
#include "IGame.h"
namespace AFG_Games {

	// Implementation of Game interface
	template<unsigned SIZE>
	class BattleShipGame : public IGame, public Singleton<BattleShipGame<SIZE>>
	{
		enum{ GRIDSIZE = SIZE * SIZE, BOATLIMIT = 5U};
		static const char OPEN = 'O', HIT = 'H', MISS = 'M';
		static char Ocean[GRIDSIZE];
	public:
		BattleShipGame<SIZE>() : IGame(1U)
		{			
				Reset();
		}
		void Reset()
		{
			for (unsigned i = 0U; i < GRIDSIZE; ++i) Ocean[i] = OPEN;
			for (unsigned i = 0U; i < BOATLIMIT; ++i)
			{
				delete Ships[i];
				switch ((rand() % 5) + 1)
				{
				case 1:
					Ships[i] = new BattleShip<1>(); break;
				case 2:
					Ships[i] = new BattleShip<2>(); break;
				case 3:
					Ships[i] = new BattleShip<3>(); break;
				case 4:
					Ships[i] = new BattleShip<4>(); break;
				default:
					Ships[i] = new BattleShip<5>(); break;
			    }
				auto ship = Ships[i];
				while (!IShip::InBounds(ship) || (i &&  IShip::Collides(ship,Ships, i)))
				{
					ship->SetRow((rand() % SIZE));
					ship->SetCol((rand() % SIZE));
				}
				std::cout << "A " << ship->name() << " is at : " << ship->Positions() << " with a "
					<< (ship->GetOrien() ? "Horizontal" : "Vertical") << " orientation." << std::endl;
				//std::cout << "A "<< ship->name() << " is at : " << ship->GetRow() <<", " << ship->GetCol() <<" with a " 
					//<< (ship->GetOrien() ? "Horizontal" : "Vertical")  <<" orientation."<< std::endl;
			}
		}
		void Instructions()
		{
			std::cout << "Please Enter A location to Fire at (" << "A1" << " to " << "J0"<<"): ";
		}
		void DisplayGame()
		{
			std::cout << std::setw(7);
			for (unsigned i = 1U; i < SIZE; ++i)
			{
				std::cout << (i) << " ";
			}
			std::cout << '0';
			std::cout << std::endl;
			for (unsigned r = 0U; r < SIZE; ++r)
			{
				std::cout << std::setw(5);
				std::cout << (char)('A' + r) << " ";
				for (unsigned c = 0U; c < SIZE; ++c)
				{
					std::cout << Ocean[(r * SIZE) + c] << " ";
				}
				std::cout << std::endl;
			}
		}
		std::string name() const
		{
			return "Battle Ship";
		}
	protected:
		unsigned  Turn()const;
		unsigned  PlayerCount()const;
		virtual void OnEndGame();
		virtual void GameLogic();
		virtual bool Playing();
		virtual void PrintResults();
		bool allSunk()const
		{
			for (unsigned i = 0U; i < BOATLIMIT; ++i)
			{
				if (!Ships[i]->isSunk())
					return false;
			}
			return true;
		}
		bool shot(char r, char c)
		{
			for (unsigned i = 0U; i < BOATLIMIT; ++i)
			{
				if (Ships[i]->shot(r, c))
				{
					Ocean[(((unsigned)(r - 'A')) * SIZE) + (unsigned)(c - '1')] = HIT;
					if (Ships[i]->isSunk()) std::cout <<"A "<< Ships[i]->name() << " has been Sunk!" << std::endl;
					return true;
				}
			}
			Ocean[(((unsigned)(r - 'A')) * SIZE) + (unsigned)(c - '1')] = MISS;
			return false;
		}
		void PlayGame()
		{
			if (!Ships[0]) Reset();
			IGame::PlayGame();
		}
	private:
		class IShip
		{
			unsigned row, col;
			bool* HitArray;
		protected:
			IShip(bool* HitArray): HitArray(HitArray)
			{
				
			}
			enum Orientation
			{
				VERTICAL, HORIZONTAL
			};
			Orientation orientation;
		public:
			std::string Positions()
			{
				return orientation == Orientation::HORIZONTAL ? GetHorizontalPos(this) : GetVerticalPos(this);
			}
			bool isSunk()const
			{
				for (unsigned i = 0; i < size(); ++i) 
					if(!HitArray[i])
						return false;
				return true;
			}
			bool& operator[](unsigned index)
			{
				return HitArray[index % size()];
			}
			void reset() { for (unsigned i = 0U; i < size(); ++i) HitArray[i] = false; };
			virtual unsigned size()const = 0;
			bool shot(char r, char c)
			{
				return orientation == Orientation::HORIZONTAL ? SearchHorizontal(this, r, c) : SearchVertical(this, r, c);
			}
			virtual std::string name()const = 0;
			void SetRow(unsigned row) { this->row = row; }
			void SetCol(unsigned col) { this->col = col; }
			unsigned GetRow() { return row; }
			unsigned GetCol() { return col; }

			Orientation GetOrien()const { return orientation; }
			void SetOrien(Orientation orientation) {  this->orientation = orientation; }
			
			static bool SearchVertical(IShip* ship, char r, char c)
			{
				unsigned R = (r - 'A'), C = (c - '1');
				
				for (unsigned i = 0U; i < ship->size(); ++i)
				{
					if ((ship->GetRow() + i) == R && (ship->GetCol()) == C)
					{
						return (*ship)[i] = true;
					}
				}
				return false;
			}
			static bool SearchHorizontal(IShip* ship, char r, char c)
			{
				unsigned R = (r - 'A'), C = (c - '1');
				for (unsigned i = 0U; i < ship->size(); ++i)
				{
					if ((ship->GetRow()) == R && (ship->GetCol() + i) == C)
					{
						return (*ship)[i] = true;
					}
				}
				return false;
			}
			static std::string GetVerticalPos( IShip* ship)
			{
				std::string list;
				for (unsigned i = 0U; i < ship->size(); ++i)
				{
					((((list += "[") += ((char)('A' + (ship->GetRow() + i)))) += " , ") += ( (char)('1' + ship->GetCol()))) += "]";
				}
				return list;
			}
			static std::string GetHorizontalPos( IShip* ship)
			{
				std::string list;
				for (unsigned i = 0U; i < ship->size(); ++i)
				{
					((((list += "[") += ((char)('A' + (ship->GetRow())))) += " , ") += ((char)('1' + ship->GetCol() + i))) += "]";
				}
				return list;
			}
			static bool InBounds(IShip* ship)
			{
				switch (ship->GetOrien())
				{
					case Orientation::HORIZONTAL:
						return ship->GetCol() + (ship->size() - 1U) < SIZE;
					case Orientation::VERTICAL:
						return ship->GetRow() + (ship->size() - 1U) < SIZE;
					default: return false;
				}
			}
			static bool Collides(IShip* shipA, IShip* shipB)
			{
				for (unsigned i = 0U; i < shipA->size() && i + shipA->GetCol() < SIZE  && i + shipA->GetRow() < SIZE; ++i)
				{
					switch (shipA->GetOrien())
					{
					case Orientation::HORIZONTAL:
						if (shipB->shot('A' + (shipA->GetRow()), '1' + (shipA->GetCol() + i)))
						{
							shipB->reset();
							return true;
						}
					case Orientation::VERTICAL:
						if (shipB->shot('A' + (shipA->GetRow() + i), '1' + (shipA->GetCol())))
						{
							shipB->reset();
							return true;
						}
					default: return false;
					}
				}
				return false;
			}
			static bool Collides(IShip* shipA, IShip* shipB[], unsigned count = BOATLIMIT)
			{
				for (unsigned i = 0U; i < count; ++i)
				{
					if (Collides(shipA, shipB[i]))
						return true;
				}
				return false;
			}
		public:
			virtual ~IShip() 
			{
				
			}
		};
		template<unsigned BOATSIZE>
		class BattleShip : public IShip
		{			
		public:
			~BattleShip() { std::cout << "Deleted a " + name() << "." << std::endl; }
			BattleShip() : IShip(HitArray)
			{
				SetRow((rand() % SIZE));
				SetCol((rand() % SIZE));
				SetOrien(rand() % 2U ? IShip::HORIZONTAL : IShip::VERTICAL);
			}
			std::string name()const
			{
				switch (BOATSIZE)
				{
				case 1U: return "Canoe";
				case 2U: return "Sail-Boat";
				case 3U: return "Tug-Boat";
				case 4U: return "Vassal";
				default: return "BattleShip";
				}
			}
			virtual unsigned size()const { return BOATSIZE; }
			
			bool HitArray[BOATSIZE];
		};
		private:
		IShip* Ships[BOATLIMIT];
	};
	#pragma region  Implementation
	template<unsigned SIZE>
	char BattleShipGame<SIZE>::Ocean[BattleShipGame<SIZE>::GRIDSIZE];
	template<unsigned SIZE>
	inline unsigned BattleShipGame<SIZE>::Turn() const
	{
		return 0U;
	}
	template<unsigned SIZE>
	inline unsigned BattleShipGame<SIZE>::PlayerCount() const
	{
		return 0U;
	}
	template<unsigned SIZE>
	inline void BattleShipGame<SIZE>::OnEndGame()
	{
		std::cout << "Play again? Y/N : ";
		char response;
		std::cin >> response;
		if (toupper(response) == 'Y')
		{ 
			return PlayGame();
		}
		else
		{
			for (unsigned i = 0U; i < BOATLIMIT; ++i)
			{
				delete Ships[i];
				Ships[i] = NULL;
			}
			std::cout << "Thanks for playing " << name() << "!" << std::endl;
		}
	}
	template<unsigned SIZE>
	inline void BattleShipGame<SIZE>::GameLogic()
	{
		char Row, Col;
		std::cin >> Row >> Col;
		// assert here
		Row = toupper(Row);
		if (Col == '0')
			Col = ':';
		
		if (shot(Row, Col))
			std::cout << "Hit!" << std::endl << std::endl;
		else std::cout << "Miss!" << std::endl << std::endl;
	}
	template<unsigned SIZE>
	inline bool BattleShipGame<SIZE>::Playing()
	{
		return !allSunk();
	}
	template<unsigned SIZE>
	inline void BattleShipGame<SIZE>::PrintResults()
	{
		DisplayGame();
		for (unsigned i = 0U; i < BOATLIMIT; ++i)
		{
			delete Ships[i];
			Ships[i] = NULL;
		}
		std::cout << "YOU'VE SUNK ALL THE BATTLE SHIPS!" << std::endl;
	}
#pragma endregion	
}