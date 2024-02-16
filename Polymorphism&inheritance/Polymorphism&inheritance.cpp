#include <iostream>
#include <random>
#include <chrono>
#include <thread>
using namespace std;
using namespace this_thread;
using namespace chrono;
class Monster
{
public:
	string Name;
	string Ability;
	int Attack;
	int MonsterLife;
	virtual int UniqeSkill() = 0;
};


class WereWolf : public Monster
{
public:
	int UniqeSkill()
	{
		cout << Name + " " + "Whoh" << endl;
		sleep_for(seconds(1));
		return 10;
	}
};


class Vampire : public Monster
{
public:
	int UniqeSkill()
	{
		cout << Name + " " + "Kiss" << endl;
		sleep_for(seconds(1));
		return 20;
	}
};


class Zombie : public Monster
{
public:
	int UniqeSkill()
	{
		cout << Name + " " + "AH AH" << endl;
		sleep_for(seconds(1));
		return 0;
	}
};


class Player
{
public:
	int PlayerLife;
	int PlayerTurn;
	string PlayerName;
	string Respone;
	bool flag;
	int RollDice(bool Respone) {
		if (Respone == false) return -1;

		return GenerateNumber();
	}
	int Fight(bool Response)
	{
		return GenerateNumber() * 10;
	}
private:
	int GenerateNumber()
	{
		random_device rd;
		mt19937 gen(rd());

		uniform_int_distribution<>  distrib(1, 2);
		return distrib(gen);
	}
};



Monster* monsters(int num)
{
	Monster* monsters[3];

	monsters[0] = new WereWolf();
	monsters[1] = new Vampire();
	monsters[2] = new Zombie();

	switch (num)
	{
	case 0:
		monsters[num]->Name = "Lucas";
		monsters[num]->Ability = "Strenght";
		monsters[num]->Attack = 20;
		monsters[num]->MonsterLife = 50;
		return monsters[num];
	case 1:
		monsters[num]->Name = "Edward";
		monsters[num]->Ability = "Inteligent";
		monsters[num]->Attack = 30;
		monsters[num]->MonsterLife = 60;
		return monsters[num];
	case 2:
		monsters[num]->Name = "Lily";
		monsters[num]->Ability = "Undead";
		monsters[num]->Attack = 10;
		monsters[num]->MonsterLife = 40;
		return monsters[num];
	}
}


void Playerlog(Monster* mon, Player player)
{
	cout << "Player Attack Enemy { " << mon->Name << "} For " << player.Fight(player.flag) << endl;
	cout << "Enemy Life " << mon->MonsterLife << endl;
	cout << "Player Life " << player.PlayerLife << endl;
    sleep_for(seconds(1));
}
void Enemylog(Monster* mon, Player player)
{
	cout << "Enemy Attack player { " << player.PlayerName << "} For " << player.Fight(player.flag) << endl;
	cout << "Player Life " << player.PlayerLife << endl;
	cout << "Enemy Life " << mon->MonsterLife << endl;
	sleep_for(seconds(1));

}

int main()
{
	int diceNum;
	Player player;

	cout << "Enter Your Name" << endl;
	cin >> player.PlayerName;

	do
	{
		cout << "Hi," << player.PlayerName << " Want to Roll A Dice ? (y/n): " << endl;
		cin >> player.Respone;
		player.PlayerTurn = 0;
		player.PlayerLife = 100;
	    int turn = 1;

		if (player.Respone == "y")
		{
			player.flag = true;
			diceNum = player.RollDice(player.flag);

			for (int i = 0; i <= diceNum; i++)
			{
				if (i == diceNum)
				{
					Monster* mon = monsters(diceNum);

					cout << "You Found A Monter " << mon->Name << endl;
					cout << "Did You want to fight (y/n) ? " << endl;
					cin >> player.Respone;

					if (player.Respone == "y")
					{
						while (mon->MonsterLife > 0)
						{
							
							if (mon->MonsterLife > 20 && player.PlayerLife > 0 &&
								player.PlayerTurn == turn)
							{
								player.PlayerLife -= mon->Attack;
								Enemylog(mon, player);
								turn++;
							}
							else if (mon->MonsterLife <= 20 && player.PlayerLife > 0 && 
								player.PlayerTurn == turn) 
							{
							    player.PlayerLife -= (int)mon->UniqeSkill();
								Enemylog(mon, player);
								player.PlayerTurn++;
							}
							else
							{
								mon->MonsterLife -= player.Fight(player.flag);
								Playerlog(mon, player);
								player.PlayerTurn++;
							}

							if (mon->MonsterLife <= 0 || player.PlayerLife <= 0)
							{
								if (mon->MonsterLife > player.PlayerLife)
								{
									cout << "Player has been defeat try again (y/n) ?" << endl;
									cin >> player.Respone;
								}
								else
								{
									cout << "enemy has been defeat Congrat!!! try again (y/n) ?" << endl;
									cin >> player.Respone;
								}
								break;
							}
						}; 
					}
					else
					{
						cout << "Have a nice Day Feel " << endl;
						break;
					}
				}
			}
		}

	} while (player.Respone == "y");

	return 0;
}
