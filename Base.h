#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Strategy.h"
#include "IObserver.h"
#include "HeroesResources.h"

class Unit;

class Base : public IObserver {
private:
    std::string base_name;
    Faction faction;
    HeroesResources resources;
    size_t current_units_count;
    size_t max_units_limit;

    int x_coord;
    int y_coord;
    char map_symbol;

public:
    Base(const std::string& name, Faction f, size_t max_units, int x = 0, int y = 0)
        : base_name(name), faction(f), current_units_count(0), max_units_limit(max_units),
        x_coord(x), y_coord(y), map_symbol('B') {
        resources.gold = 2000;
        resources.wood = 15;
        resources.ore = 15;
        resources.mercury = 5;
        resources.sulfur = 0;
        resources.crystals = 0;
        resources.gems = 0;
    }

    Faction get_faction() const { return faction; }
    std::string get_name() const { return base_name; }
    int get_x() const { return x_coord; }
    int get_y() const { return y_coord; }
    char get_symbol() const { return map_symbol; }

    bool can_recruit() const {
        return current_units_count < max_units_limit;
    }

    void register_new_unit(Unit* unit) {
        if (unit) {
            unit->register_observer(this);
            current_units_count++;
            std::cout << "[База " << base_name << "] Нанят новый юнит. Текущий гарнизон: "
                << current_units_count << "/" << max_units_limit << "\n";
        }
    }

    void on_unit_death(Unit* dead_unit) override {
        if (current_units_count > 0) {
            current_units_count--;
        }
        std::cout << "[База-Наблюдатель] Замок оповещен: погиб наш воин. Место в гарнизоне освобождено: "
            << current_units_count << "/" << max_units_limit << "\n";
    }

    void add_resources(const HeroesResources& res) {
        resources.gold += res.gold;
        resources.wood += res.wood;
        resources.ore += res.ore;
        resources.mercury += res.mercury;
        resources.sulfur += res.sulfur;
        resources.crystals += res.crystals;
        resources.gems += res.gems;
    }

    void print_status() const {
        std::cout << "Статус Замка: " << base_name << "\n"
            << "Золото: " << resources.gold << " | Дерево: " << resources.wood
            << " | Руда: " << resources.ore << " | Ртуть: " << resources.mercury << "\n"
            << "Гарнизон замка: " << current_units_count << " / " << max_units_limit << "\n";
    }
};
