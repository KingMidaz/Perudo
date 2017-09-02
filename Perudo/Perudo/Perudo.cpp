#include "Perudo.h"
#include "Player.h"
#include "Dice.h"
#include <string>
#include <cctype>
#include <algorithm>

int getQuant(int num, int players, std::vector<Player> PlayerArr)
{
	int cnt = 0;

	if (num == 1)
	{
		for(int i = 0; i < players; i ++)
		{
			cnt += PlayerArr[i].GetDiceCountNum(num);
		}
	}
	else
	{
		for (int i = 0; i < players; i++)
		{
			cnt += PlayerArr[i].GetDiceCountNum(num);
			cnt += PlayerArr[i].GetDiceCountNum(1);
		}
	}

	return cnt;
}

bool GameOver(int players, std::vector<Player> PlayerArr)
{
	int cnt = 0;

	for(int i = 0; i < players; i++)
	{
		if (!PlayerArr[i].getHasLost()) { cnt++; }
	}
	if (cnt > 1) { return false; }
	else { return true; }
}

int main()
{	
	int NUMPLAYERS = 0;
	int NUMDICE = 1;
	
	std::vector<Player> PlayerArr;
	std::string name;
	
	std::cout << "Enter name. Enter done to start." << std::endl;

	while(std::getline(std::cin, name) && name.compare("done") != 0)
	{
		NUMPLAYERS++;
		PlayerArr.emplace_back(NUMDICE, name);
		std::cout << "Enter name. Enter done to start." << std::endl;
	}

	int Round = 1;
	int playerTurn = 0;
	
	while (!GameOver(NUMPLAYERS, PlayerArr))
	{
		int Dice = 0;
		for (int i = 0; i < NUMPLAYERS; i++)
		{
			Dice += PlayerArr[i].getDice();
		}

		std::cout << "Round " << Round << std::endl;
		std::cout << "Dice in play " << Dice << std::endl;

		for (int i = 0; i < NUMPLAYERS; i++)
		{
			PlayerArr[i].RollDice();
		}

		bool callBluff = false;
		std::string line;

		int MoveNum = 0;
		int MoveQuant = 0;
		int NextMoveNum = 0;
		int NextMoveQuant = 0;

		while (!callBluff)
		{
			std::cout << PlayerArr[playerTurn].getName() << "'s turn" << std::endl;

			std::getline(std::cin, line);
			if (std::isdigit(line.front()))
			{
				NextMoveQuant = std::stoi(line.substr(0, line.find_first_of(" ")));
				NextMoveNum = std::stoi(line.substr(line.find_first_of(" ") + 1));

				if (NextMoveNum < 7 && NextMoveNum > 0 && NextMoveNum == 1 && ((NextMoveNum == 1 && NextMoveQuant > MoveQuant)
					|| (NextMoveNum != 1 && NextMoveQuant > MoveQuant * 2 + 1)) || ((NextMoveNum == 1 && NextMoveQuant > (MoveQuant - 1) / 2)
						|| (NextMoveNum != 1 && NextMoveQuant > MoveQuant) || (NextMoveNum != 1 && NextMoveNum > MoveNum && NextMoveQuant >= MoveQuant)))
				{
					MoveNum = NextMoveNum;
					MoveQuant = NextMoveQuant;

					if (playerTurn == NUMPLAYERS - 1) { playerTurn = 0; }
					else { playerTurn++; }
				}
				else
				{
					char s[] = "Illegal move, please try again";
					std::cout << s << std::endl;
				}
			}
			else if (line.compare("bluff") == 0 || line.compare("Bluff") == 0)
			{
				callBluff = true;

				int pt = 0;
				if (playerTurn == 0) { pt = NUMPLAYERS - 1; }
				else { pt = playerTurn - 1; }

				if (getQuant(MoveNum, NUMPLAYERS, PlayerArr) >= MoveQuant)
				{
					PlayerArr[playerTurn].LoseDice();
					std::cout << "Bluff call was unsuccessful. " << PlayerArr[playerTurn].getName() << " has lost a dice." << std::endl;
				}
				else
				{
					playerTurn = pt;
					PlayerArr[pt].LoseDice();
					std::cout << "Bluff call was successful. " << PlayerArr[pt].getName() << " has lost a dice." << std::endl;
				}
			}
			else
			{
				char s[] = "Illegal move, please try again";
				std::cout << s << std::endl;
			}
		}

		Round++;
	}

	for (int i = 0; i < NUMPLAYERS; i++)
	{
		if (!PlayerArr[i].getHasLost()) { std::cout << PlayerArr[i].getName() << " is the WINNER!!" << std::endl; }
	}
	
	std::cout << "Press Enter to Continue..." << std::endl;
	std::cin.ignore();
}
