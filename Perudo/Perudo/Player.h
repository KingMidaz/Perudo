#pragma once

#include "Perudo.h"
#include "Dice.h"

class Player
{
public:
	Player(int maxdice, std::string playerName)
	{
		MAXDICE = maxdice;
		hasLost = false;
		PlayerName = playerName;

		for (int i = 0; i < MAXDICE; i++)
		{
			DiceArr.emplace_back();
		}
	}

	void LoseDice();
	int GetDiceCountNum(int) const;
	void SetMaxDice(int);
	std::string getName();
	int getDice() const;
	bool getHasLost() const;
	void RollDice();

private:
	int MAXDICE;
	bool hasLost;

	std::string PlayerName;

	std::vector<Dice> DiceArr;
};
