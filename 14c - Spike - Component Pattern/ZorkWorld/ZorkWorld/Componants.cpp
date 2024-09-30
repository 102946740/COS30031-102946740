#include "Componants.h"
#include "Inventory.h"
#include <string>

bool Attributes::dealDamage(int Dmg)
{
	HP -= Dmg;

	if (HP != 0) {
		return true;
	}

	return false;

}

std::string Attributes::getDetails() const
{
	return "HP: " + std::to_string(HP), + ", Damage: " + std::to_string(Damage) + ", Can Interact? " + (Interactable ? "Yes" : "No") + ", Alive? " + (Alive ? "Yes" : "No");
}

std::string Identifier::getIdentifiers() const
{
	return "Name: " + Name + ", Decription: " + Description;
}

void InventoryComp::addItem(Item ItemAdded)
{
	Items.push_back(ItemAdded);
}

void InventoryComp::removeItem(int index)
{
	std::cout << "Removed: " << Items[index].ID.Name << "\n";
	Items.erase(Items.begin() + index);
}

void InventoryComp::printInventory(std::string name) const
{
	std::cout << "Showing Inventory of " << name << "\n";
	int count = 1;
	for (Item item : Items) {
		std::cout << item.ID.getIdentifiers() << item.stats.getDetails() << "\n";

		count++;
	}
	std::cout << "\nEnd of inventory\n\n";
}
