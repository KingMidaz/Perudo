#pragma once

#include <random>
#include "Perudo.h"

class Dice
{
public:
	int GetNum() const;

	void RollNum();

private:
	int Roll = 0;
};