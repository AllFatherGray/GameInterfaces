#include "GameLibrary.h"
using namespace AFG_Games;
int main()
{
	//AFG_Games::GameLibrary& g = AFG_Games::GameLibrary::Instance();
	//std::cout << &g << " "<<&AFG_Games::GameLibrary::Instance();
	//std::cout << &Singleton<AFG_Games::GameLibrary>::Instance() << " " << &AFG_Games::GameLibrary::Instance()<< std::endl;
	//std::cout << &Singleton<AFG_Games::GameLibrary>::Instance() << " " << &AFG_Games::GameLibrary::Instance();
	GameLibrary::OpenMenu();
	return 0;
}