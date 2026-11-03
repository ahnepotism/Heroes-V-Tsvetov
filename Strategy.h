#pragma once
#include <string>
#include <iostream>

enum class Faction { Haven, Inferno, Sylvan, Dungeon, Academy, Necropolis, Stronghold };

class Unit;

class InteractionStrategy {
public:
    virtual ~InteractionStrategy() = default;
    virtual void apply(Unit& unit) = 0;
};

class AttackBoostStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override;
};

class HealthRestoreStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override;
};

class ManaBoostStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override;
};
