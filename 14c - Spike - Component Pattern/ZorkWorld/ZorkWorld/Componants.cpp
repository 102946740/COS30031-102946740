#include "Componants.h"
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
