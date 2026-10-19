#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "Unit.h"

class GameField {
private:
	int width, height;
	size_t max_units;
	std::vector<std::unique_ptr<Unit>> units;
public:
	GameField(int w, int h, size_t max_u) : width(w), height(h), max_units(max_u) {}

	GameField(const GameField& other) : width(other.width), height(other.height), max_units(other.max_units) {
		for (const auto& u : other.units) {
			if (u) units.push_back(u->clone());
		}
	}
    GameField& operator=(const GameField& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            max_units = other.max_units;
            units.clear();
            for (const auto& u : other.units) {
                if (u) units.push_back(u->clone());
            }
        }
        return *this;
    }

    GameField(GameField&& other) noexcept
        : width(other.width), height(other.height), max_units(other.max_units), units(std::move(other.units)) {
        other.width = 0; other.height = 0; other.max_units = 0;
    }

    GameField& operator=(GameField&& other) noexcept {
        if (this != &other) {
            width = other.width;
            height = other.height;
            max_units = other.max_units;
            units = std::move(other.units);
            other.width = 0; other.height = 0; other.max_units = 0;
        }
        return *this;
    }

    ~GameField() = default;


    bool add_unit(std::unique_ptr<Unit> unit) {
        if (!unit) return false;
        if (units.size() >= max_units) {
            std::cout << "[Ошибка] Превышен лимит юнитов на поле!\n";
            return false;
        }
        if (unit->get_x() < 0 || unit->get_x() >= width || unit->get_y() < 0 || unit->get_y() >= height) {
            std::cout << "[Ошибка] Координаты юнита выходят за границы поля!\n";
            return false;
        }
        units.push_back(std::move(unit));
        return true;
    }

    void move_unit(size_t index, int new_x, int new_y) {
        if (index >= units.size()) return;
        if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
            units[index]->set_coordinates(new_x, new_y);
        }
    }

    void remove_dead_units() {
        for (auto it = units.begin(); it != units.end(); ) {
            if ((*it)->get_health_obj().is_dead()) {
                std::cout << "Юнит " << (*it)->get_type() << " погиб и удален.\n";
                it = units.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    bool remove_unit_by_index(size_t index) {
        if (index >= units.size()) {
            std::cout << "[Ошибка] Юнита с индексом " << index << " не существует!\n";
            return false;
        }

        std::cout << "Юнит " << units[index]->get_type() << " был принудительно удален игроком.\n";
        units.erase(units.begin() + index);
        return true;
    }


    void display() const {
        std::vector<std::vector<char>> display_grid(height, std::vector<char>(width, ' '));
        for (const auto& u : units) {
            if (u->get_x() >= 0 && u->get_x() < width && u->get_y() >= 0 && u->get_y() < height) {
                display_grid[u->get_y()][u->get_x()] = u->get_symbol();
            }
        }

        for (int x = 0; x < width + 2; ++x) {
            std::cout << "X ";
        }
        std::cout << '\n';

        for (int y = 0; y < height; ++y) {
            std::cout << "X "; 
            for (int x = 0; x < width; ++x) {
                std::cout << display_grid[y][x] << ' ';
            }
            std::cout << "X \n";
        }

        for (int x = 0; x < width + 2; ++x) {
            std::cout << "X ";
        }
        std::cout << "\n\n";
    }



    auto begin() { return units.begin(); }
    auto end() { return units.end(); }
    auto begin() const { return units.begin(); }
    auto end() const { return units.end(); }
    size_t get_units_count() const { return units.size(); }
};