#pragma once

class Health {
private:
	int current_health;
public:
	Health(int start_hp) {
		if (start_hp < 0) {
			current_health = 0;
		}
		else {
			current_health = start_hp;
		}
	}

	int get_health() const {
		return current_health;
	}

	void damage(int damage_amount) {
		if (damage_amount > 0) {
			if (current_health - damage_amount < 0) {
				current_health = 0;
			}
			else {
				current_health = current_health - damage_amount;
			}
		}
	}

	void heal(int heal_amount) {
		if (heal_amount > 0) {
			current_health += heal_amount;
		}
	}

	bool is_dead() const {
		return current_health == 0;
	}
};