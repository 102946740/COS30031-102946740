#pragma once
struct itemStruc {
    std::string Identifier;
    std::string Name;
    std::string Description;
    int EffectMod = 0;
};
class Entity {
public:
    virtual ~Entity() = default;
    itemStruc Info;
    bool Interactable = true;
    virtual void loadFromJson(const nlohmann::json& json);

    virtual void printEntity() const;
};