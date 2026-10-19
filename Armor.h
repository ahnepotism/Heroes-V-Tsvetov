#pragma once

class Armor {
private:
	int armor_value;
public:
	Armor(int start_armor) {
		if (start_armor < 0) {
			armor_value = 0;
		}
		else {
			armor_value = start_armor;
		}
	}

	int get_armor() const {
		return armor_value;
	}

	int reduce(int damage_amount) const {
		if (damage_amount <= 0) {
			return 0;
		}
		int effective_damage = damage_amount - armor_value;

		if (effective_damage < 0) {
			return 0;
		}
		else {
			return effective_damage;
		}
	}
};