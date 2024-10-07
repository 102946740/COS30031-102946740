#include "Componants.h"  
#include "Entity.h"
#include <string>

// Attributes Class Implementation
bool Attributes::dealDamage(int Dmg) {
    HP -= Dmg;

    // Check if HP is less than or equal to 0 to determine if the entity is alive
    if (HP <= 0) {
        Alive = false;  // Mark as not alive
        return false;   // Return false, as the entity is no longer alive
    }

    return true; // Return true, as the entity is still alive
}

std::string Attributes::getDetails() const {
    return "HP: " + std::to_string(HP) +
        ", Damage: " + std::to_string(Damage) +
        ", Can Interact? " + (Interactable ? "Yes" : "No") +
        ", Alive? " + (Alive ? "Yes" : "No");
}

// Identifier Class Implementation
std::string Identifier::getIdentifiers() const {
    return "Name: " + Name + ", Description: " + Description; // Fixed "Decription" to "Description"
}

// InventoryComp Class Implementation
void InventoryComp::addItem(std::shared_ptr<Entity> ItemAdded) {
    Items.push_back(ItemAdded); 
}

void InventoryComp::removeItem(int index) {
    if (index >= 0 && index < Items.size()) {
        std::cout << "Removed: " << Items[index]->compManager.getComponent<Identifier>()->Name << "\n";
        Items.erase(Items.begin() + index); 
    }
    else {
        std::cout << "Invalid index for removal.\n";
    }
}

void InventoryComp::printInventory(const std::string& name) const {
    std::cout << "Showing Inventory of " << name << "\n" << "Amount of Items: " << Items.size() << "\n";

    if (Items.empty()) {
        std::cout << "No items in inventory.\n"; 
        return;
    }

    int count = 1;
    for (const auto& item : Items) {
        // Check if item is valid
        if (!item) {
            std::cout << "Item " << count << ": Invalid item pointer.\n";
            count++;
            continue; // Skip to next item if the current one is invalid
        }

        auto identifier = item->compManager.getComponent<Identifier>();
        auto stats = item->compManager.getComponent<Attributes>();

        // Check if identifier and stats are valid
        if (!identifier) {
            std::cout << "Item " << count << ": No Identifier component.\n";
        }
        else {
            std::cout << "Item " << count << ": " << identifier->getIdentifiers(); // Print identifier
        }

        if (!stats) {
            std::cout << " - No Attributes component.\n"; // Indicate absence of Attributes
        }
        else {
            std::cout << ", " << stats->getDetails(); // Print stats details
        }

        std::cout << "\n"; // Move to the next line after printing item details
        count++;
    }

    std::cout << "End of inventory\n\n";
}

