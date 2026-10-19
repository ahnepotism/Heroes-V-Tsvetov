#pragma once

#include "Armor.h"

class Attack {
private:
	int damage_value;
public:
	Attack(int start_damage) {
		if (start_damage < 0) {
			damage_value = 0;
		}
		else {
			damage_value = start_damage;
		}
	}

	int get_damage() const {
		return damage_value;
	}

	int calculate_damage(const Armor& target_armor) {
		return target_armor.reduce(damage_value);
	}
};
