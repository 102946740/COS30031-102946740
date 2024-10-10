#include "MessageHandler.h"

bool MessageHandler::attack(std::string itemA, std::string itemB)
{
    auto finderA = Entities.find(itemA);
    if (finderA != Entities.end()) {
        auto finderB = Entities.find(itemB);
        if (finderB != Entities.end()) { // finds both entity 1 and 2

            auto Attacker = finderB->second->compManager.getComponent<Attributes>();
            auto Receiver = finderA->second->compManager.getComponent<Attributes>();
            if (Receiver && Attacker) {
                int damage = Receiver->dealDamage(Attacker->Damage);
                std::cout << "Health of " << finderA->first << ": " << damage << "\n";
                return true;
            }
            

        }
    }


    return false;
}
