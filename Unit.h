#pragma once
#include <string>
#include <memory>
#include "Health.h"
#include "Armor.h"
#include "Attack.h"

class Unit {
protected:
	Health health;
	Armor armor;
	Attack attack;
	int x_coord;
	int y_coord;
	char map_symbol;
public:
	Unit(Health h, Armor a, Attack att, int start_x, int start_y, char symbol)
		: health(h), armor(a), attack(att), x_coord(start_x), y_coord(start_y), map_symbol(symbol) {
	}

	virtual ~Unit() = default;

	virtual std::unique_ptr<Unit> clone() const = 0;

	virtual std::string get_type() const = 0;

	int get_x() const {
		return x_coord;
	}
	int get_y() const {
		return y_coord;
	}
	char get_symbol() const {
		return map_symbol;
	}

	const Health& get_health_obj() const {
		return health;
	}
	const Armor& get_armor_obj() const {
		return armor;
	}
	const Attack& get_attack_obj() const {
		return attack;
	}

	void set_coordinates(int new_x, int new_y) {
		x_coord = new_x;
		y_coord = new_y;
	}

	void take_damage(int damage_amount) {
		health.damage(damage_amount);
	}
};