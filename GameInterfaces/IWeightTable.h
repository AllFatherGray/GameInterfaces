#pragma once
#include <iostream>
template<unsigned TurnCount, unsigned ROW, unsigned COL>
struct IWeightTable
{
	void DisplayWeightTable()
	{

	}
	virtual void UpdateTable() = 0;
protected:
	unsigned Table[TurnCount][ROW * COL];
	//unsigned Table[TurnCount][ROW * COL];
};