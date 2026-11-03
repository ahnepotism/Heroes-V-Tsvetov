#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Strategy.h"
#include "HeroesResources.h"

class NeutralObject : public GameObject {
public:
    NeutralObject(int x, int y, char symbol) : GameObject(x, y, symbol) {}
    virtual ~NeutralObject() = default;

    std::string get_type() const override { return "NeutralObject"; }
    virtual std::string get_color_code() const = 0;
};

class GoldChest : public NeutralObject {
private:
    HeroesResources loot;
public:
    GoldChest(int x, int y) : NeutralObject(x, y, '$') {
        loot.gold = 500;
        loot.wood = 5;
    }
    std::unique_ptr<GameObject> clone() const override { return std::make_unique<GoldChest>(*this); }
    std::string get_type() const override { return "Gold Chest"; }
    std::string get_color_code() const override { return "\033[1;93m"; }
    HeroesResources get_loot() const { return loot; }
};

class SpikeTrap : public NeutralObject {
public:
    SpikeTrap(int x, int y) : NeutralObject(x, y, '^') {}
    std::unique_ptr<GameObject> clone() const override { return std::make_unique<SpikeTrap>(*this); }
    std::string get_type() const override { return "Spike Trap"; }
    std::string get_color_code() const override { return "\033[1;91m"; }
};

class Altar : public NeutralObject {
public:
    std::unique_ptr<InteractionStrategy> strategy;

    Altar(int x, int y, std::unique_ptr<InteractionStrategy> strat)
        : NeutralObject(x, y, 'A'), strategy(std::move(strat)) {
    }

    Altar(const Altar& other) : NeutralObject(other.x_coord, other.y_coord, 'A') {
        if (dynamic_cast<AttackBoostStrategy*>(other.strategy.get())) {
            strategy = std::make_unique<AttackBoostStrategy>();
        }
        else if (dynamic_cast<HealthRestoreStrategy*>(other.strategy.get())) {
            strategy = std::make_unique<HealthRestoreStrategy>();
        }
        else {
            strategy = std::make_unique<ManaBoostStrategy>();
        }
    }

    std::unique_ptr<GameObject> clone() const override { return std::make_unique<Altar>(*this); }
    std::string get_type() const override { return "Altar"; }
    std::string get_color_code() const override { return "\033[1;96m"; }
};
