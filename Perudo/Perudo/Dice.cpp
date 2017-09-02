#include "Dice.h"


int Dice::GetNum() const
{
	return Roll;
}

void Dice::RollNum()
{
	std::random_device rd;	
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 6);
	Roll = dist(mt);
}
