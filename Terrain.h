#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "Strategy.h"

class Terrain {
public:
    virtual ~Terrain() = default;
    virtual bool is_passable(Faction faction) const = 0;
    virtual double get_speed_modifier(Faction faction) const = 0;
    virtual std::string get_color_start() const = 0;
    virtual char get_char_symbol() const = 0;
};

class Forest : public Terrain {
public:
    bool is_passable(Faction) const override { return true; }
    double get_speed_modifier(Faction faction) const override {
        if (faction == Faction::Sylvan) return 1.5;
        if (faction == Faction::Stronghold) return 0.3;
        return 0.6;
    }
    std::string get_color_start() const override { return "\033[32m"; }
    char get_char_symbol() const override { return '*'; }
};

class Plain : public Terrain {
public:
    bool is_passable(Faction) const override { return true; }
    double get_speed_modifier(Faction faction) const override {
        if (faction == Faction::Haven || faction == Faction::Academy) return 1.2;
        if (faction == Faction::Inferno) return 0.8;
        return 1.0;
    }
    std::string get_color_start() const override { return "\033[38;5;222m"; }
    char get_char_symbol() const override { return '*'; }
};

class Underworld : public Terrain {
public:
    bool is_passable(Faction) const override { return true; }
    double get_speed_modifier(Faction faction) const override {
        if (faction == Faction::Inferno || faction == Faction::Necropolis || faction == Faction::Dungeon) return 1.3;
        if (faction == Faction::Haven || faction == Faction::Sylvan) return 0.7;
        return 1.0;
    }
    std::string get_color_start() const override { return "\033[38;5;239m"; }
    char get_char_symbol() const override { return '*'; }
};

class Swamp : public Terrain {
public:
    bool is_passable(Faction) const override { return true; }
    double get_speed_modifier(Faction faction) const override {
        if (faction == Faction::Necropolis) return 1.0;
        if (faction == Faction::Inferno) return 0.2;
        return 0.4;
    }
    std::string get_color_start() const override { return "\033[38;5;94m"; }
    char get_char_symbol() const override { return '*'; }
};

class TerrainProxy : public Terrain {
private:
    std::shared_ptr<Terrain> real_terrain;
public:
    TerrainProxy(std::shared_ptr<Terrain> terrain) : real_terrain(terrain) {}

    bool is_passable(Faction faction) const override {
        std::cout << "[Прокси Ландшафта] Проверка проходимости для фракции: " << static_cast<int>(faction) << "\n";
        if (faction == Faction::Academy) {
            std::cout << "  [Прокси] Юнит левитирует! Проход разрешен автоматически.\n";
            return true;
        }
        return real_terrain->is_passable(faction);
    }

    double get_speed_modifier(Faction faction) const override {
        std::cout << "[Прокси Ландшафта] Логирование: Расчет влияния скорости фракции " << static_cast<int>(faction) << "\n";
        return real_terrain->get_speed_modifier(faction);
    }

    std::string get_color_start() const override { return real_terrain->get_color_start(); }
    char get_char_symbol() const override { return real_terrain->get_char_symbol(); }
};
