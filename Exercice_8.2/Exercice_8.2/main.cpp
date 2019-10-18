#include <iostream>
#include <vector>
#include <fstream>
#include "dragon.h"
#include "json.hpp"

using json = nlohmann::json;

int main() {

	json jDragon;

	std::ifstream inFileD("Dragon.json");

	inFileD >> jDragon;

	

	json jPig;

	std::ifstream inFileP("Pig.json");

	inFileP >> jPig;

	

	Dragon dragon = Dragon(jDragon["health"], jDragon["attack"]);

	inFileD.close();

	std::vector<Pig> pigs;

	const auto nbPig = 10;
	
	pigs.reserve(nbPig);
	for(auto i = 0; i < nbPig; i++)
	{
		pigs.emplace_back(Pig(jPig["health"], jPig["attack"]));
	}

	inFileP.close();

	bool finish = false;
	while(!finish)
	{
		//Dragon attack
		for (auto& pig : pigs)
		{
			if(pig.IsAlive())
			{
				dragon.Attack(pig);
				break; //Dragon attack once
			}
		}
		
		//Pigs attack
		for (auto& pig : pigs)
		{
			pig.Attack(dragon);
		}

		//print Dragon
		dragon.Print();

		//print Pigs
		for (auto& pig : pigs)
		{
			pig.Print();
		}

		std::cout << "=======================\n";

		//Victory conditions
		if(!dragon.IsAlive())
		{
			finish = true;
		}

		bool allPigsDead = true;
		for (auto& pig : pigs)
		{
			if(pig.IsAlive())
			{
				allPigsDead = false;
				break;
			}
		}
		if(allPigsDead)
		{
			finish = true;
		}
	}
	system("pause");
	return 0;

}