#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "Unit.h"
#include "GameException.h"
#include "IObserver.h"
#include "Terrain.h"
#include "NeutralObject.h"



class GameField : public IObserver {
private:
    int width, height;
    size_t max_units;
    std::vector<std::unique_ptr<GameObject>> units;

public:

    Unit* get_unit_ptr_by_coords(int x, int y) const {
        for (size_t i = 0; i < units.size(); ++i) {
            Unit* u = dynamic_cast<Unit*>(units[i].get());
            if (u && u->get_x() == x && u->get_y() == y) {
                return u;
            }
        }
        return nullptr;
    }

    int find_unit_index_by_coords(int x, int y) const {
        for (size_t i = 0; i < units.size(); ++i) {
            if (dynamic_cast<Unit*>(units[i].get()) && units[i]->get_x() == x && units[i]->get_y() == y) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

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

    bool add_unit(std::unique_ptr<GameObject> unit) {
        if (!unit) return false;

        if (units.size() >= max_units) {
            throw FieldLimitException();
        }
        if (unit->get_x() < 0 || unit->get_x() >= width || unit->get_y() < 0 || unit->get_y() >= height) {
            throw OutOfBoundsException(unit->get_x(), unit->get_y(), width, height);
        }
        for (const auto& u : units) {
            if (u && u->get_x() == unit->get_x() && u->get_y() == unit->get_y()) {
                throw CellOccupiedException(unit->get_x(), unit->get_y());
            }
        }

    // Наблюдатель
        Unit* unit_ptr = dynamic_cast<Unit*>(unit.get());
        if (unit_ptr) {
            unit_ptr->register_observer(this);
        }

        units.push_back(std::move(unit));
        return true;
    }

    void on_unit_death(Unit* dead_unit) override {
        for (auto it = units.begin(); it != units.end(); ++it) {
            if (it->get() == dead_unit) {
                std::cout << "Оповещение: Юнит " << dead_unit->get_type()
                    << " погиб. Поле автоматически очищает клетку ("
                    << dead_unit->get_x() << ", " << dead_unit->get_y() << ").\n";
                units.erase(it);
                break;
            }
        }
    }

    bool remove_unit_by_coordinates(int x, int y) {
        for (auto it = units.begin(); it != units.end(); ++it) {
            if (*it && (*it)->get_x() == x && (*it)->get_y() == y) {
                std::cout << "Объект " << (*it)->get_type() << " принудительно удален из клетки (" << x << ", " << y << ").\n";
                units.erase(it);
                return true;
            }
        }
        throw ObjectNotFoundException(x, y);
    }

    void move_unit(size_t index, int new_x, int new_y, Base* player_base = nullptr) {
        if (index >= units.size()) return;
        if (new_x < 0 || new_x >= width || new_y < 0 || new_y >= height) {
            std::cout << "Ошибка: Ход за границы поля заблокирован!\n";
            return;
        }

        Unit* walker = dynamic_cast<Unit*>(units[index].get());
        if (!walker) return;

        walker->set_coordinates(new_x, new_y);
        std::cout << "Юнит " << walker->get_type() << " перешел в клетку (" << new_x << ", " << new_y << ").\n";

        for (auto it = units.begin(); it != units.end(); ) {
            NeutralObject* obj_ptr = dynamic_cast<NeutralObject*>(it->get());

            if (obj_ptr && static_cast<GameObject*>(obj_ptr) != static_cast<GameObject*>(walker) && obj_ptr->get_x() == new_x && obj_ptr->get_y() == new_y) {
                std::cout << "Обнаружено взаимодействие с объектом: " << obj_ptr->get_type() << "\n";

                if (auto* chest = dynamic_cast<GoldChest*>(obj_ptr)) {
                    if (player_base) {
                        *walker + std::make_pair(chest, player_base);
                    }
                    it = units.erase(it);
                    return;
                }
                else if (auto* trap = dynamic_cast<SpikeTrap*>(obj_ptr)) {
                    *walker - *trap;
                    it = units.erase(it);
                    return;
                }
                else if (auto* altar = dynamic_cast<Altar*>(obj_ptr)) {
                    *walker** altar;
                    return;
                }
            }
            else {
                ++it;
            }
        }
    }



    void remove_dead_units() {
        for (auto it = units.begin(); it != units.end(); ) {
            Unit* unit_ptr = dynamic_cast<Unit*>(it->get());

            if (unit_ptr && unit_ptr->get_health_obj().is_dead()) {
                std::cout << "Юнит " << unit_ptr->get_type() << " погиб и удален.\n";
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

    void display(const std::vector<std::vector<std::shared_ptr<Terrain>>>& map_terrain, const Base& player_base) const {
        std::string color_reset = "\033[0m";

        for (int x = 0; x < width + 2; ++x) {
            std::cout << "X ";
        }
        std::cout << '\n';

        for (int y = 0; y < height; ++y) {
            std::cout << "X ";

            for (int x = 0; x < width; ++x) {
                std::string cell_color = map_terrain[y][x]->get_color_start();
                char cell_char = map_terrain[y][x]->get_char_symbol();

                if (player_base.get_x() == x && player_base.get_y() == y) {
                    cell_char = player_base.get_symbol();
                    cell_color = "\033[1;33m";
                }

                for (const auto& obj : units) {
                    if (obj && obj->get_x() == x && obj->get_y() == y) {
                        cell_char = obj->get_symbol();

                        auto* neutral_ptr = dynamic_cast<NeutralObject*>(obj.get());
                        if (neutral_ptr) {
                            cell_color = neutral_ptr->get_color_code();
                        }
                        else {
                            cell_color = "\033[1;37m";
                        }
                    }
                }

                std::cout << cell_color << cell_char << " " << color_reset;
            }
            std::cout << "X \n";
        }

        for (int x = 0; x < width + 2; ++x) {
            std::cout << "X ";
        }
        std::cout << "\n\n";
    }



    class Iterator {
    private:
        std::vector<std::unique_ptr<GameObject>>& ref_units;
        size_t index;
    public:
        Iterator(std::vector<std::unique_ptr<GameObject>>& u, size_t start_idx)
            : ref_units(u), index(start_idx) {
        }

        GameObject& operator*() const { return *ref_units[index]; }
        GameObject* operator->() const { return ref_units[index].get(); }

        Iterator& operator++() {
            index++;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index;
        }

        void remove() {
            if (index < ref_units.size()) {
                std::cout << "Объект " << ref_units[index]->get_type() << " погиб и удалён.\n";
                ref_units.erase(ref_units.begin() + index);
            }
        }
    };

    class ConstIterator {
    private:
        const std::vector<std::unique_ptr<GameObject>>& ref_units;
        size_t index;

    public:
        ConstIterator(const std::vector<std::unique_ptr<GameObject>>& u, size_t start_idx)
            : ref_units(u), index(start_idx) {
        }

        const GameObject& operator*() const { return *ref_units[index]; }
        const GameObject* operator->() const { return ref_units[index].get(); }

        ConstIterator& operator++() {
            index++;
            return *this;
        }

        bool operator!=(const ConstIterator& other) const {
            return index != other.index;
        }
    };

    Iterator begin() { return Iterator(units, 0); }
    Iterator end() { return Iterator(units, units.size()); }

    ConstIterator begin() const { return ConstIterator(units, 0); }
    ConstIterator end() const { return ConstIterator(units, units.size()); }

    size_t get_units_count() const { return units.size(); }
};
