#include "Player.h"

void Player::LoseDice()
{
	MAXDICE--;
	DiceArr.pop_back();

	if (MAXDICE > 0) { return; }
	else { hasLost = true; }
}

int Player::GetDiceCountNum(int num) const
{
	int cnt = 0;

	for (int i = 0; i < MAXDICE; i++)
	{
		if (DiceArr[i].GetNum() == num) { cnt++; }
	}

	return cnt;
}

void Player::SetMaxDice(int max)
{
	MAXDICE = max;
}

std::string Player::getName()
{
	return PlayerName;
}

int Player::getDice() const
{
	return MAXDICE;
}

bool Player::getHasLost() const
{
	return hasLost;
}

void Player::RollDice()
{
	for(int i = 0; i < MAXDICE; i++)
	{
		DiceArr[i].RollNum();
	}
}

