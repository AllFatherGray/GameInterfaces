#include "GameLibrary.h"
using namespace AFG_Games;
int main(int argc, char *argv[])
{
	//AFG_Games::GameLibrary& g = AFG_Games::GameLibrary::Instance();
	//std::cout << &g << " "<<&AFG_Games::GameLibrary::Instance();
	//std::cout << &Singleton<AFG_Games::GameLibrary>::Instance() << " " << &AFG_Games::GameLibrary::Instance()<< std::endl;
	//std::cout << &Singleton<AFG_Games::GameLibrary>::Instance() << " " << &AFG_Games::GameLibrary::Instance();
	//IGame::SetAssets(argc, argv);
	//std::string s = BattleShipGame<10>::Instance().name();
	//TicTacToe::Instance();
	GameLibrary::OpenMenu(argc, argv);
	return 0;
}