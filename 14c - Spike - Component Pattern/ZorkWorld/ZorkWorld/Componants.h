#pragma once
#include <iostream>
#include <vector>

class Item;

class Component {

};

class Attributes : public Component {
public:
	int HP = 0;
	int Damage = 0;
	bool Interactable = true;
	bool Alive = true;

	bool dealDamage(int Dmg);
	std::string getDetails() const;
};

class Identifier : public Component {
public:
	std::string Name = "";
	std::string Description = "";
	std::string getIdentifiers() const;
};

class InventoryComp : public Component {
public:
	bool Interactable = true;
	std::vector<Item> Items;

	void addItem(Item ItemAdded);
	void removeItem(int index);
	void printInventory(std::string name) const;
};