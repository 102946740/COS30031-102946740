#pragma once
#include <iostream>

class Attributes {
public:
	int HP = 0;
	int Damage = 0;
	bool Interactable = true;
	bool Alive = true;

	bool dealDamage(int Dmg);
	std::string getDetails() const;
};

class Identifier {
public:
	std::string Name = "";
	std::string Description = "";
	std::string getIdentifiers() const;
};