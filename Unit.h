#pragma once
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "Health.h"
#include "Armor.h"
#include "Attack.h"
#include "GameObject.h"
#include "Strategy.h"
#include "IObserver.h"
#include "NeutralObject.h"

class Base;

class Unit : public GameObject {
protected:
	Health health;
	Armor armor;
	Attack attack;
	Faction faction;
	std::vector<IObserver*> observers;

public:
	Unit(Health h, Armor a, Attack att, Faction f, int start_x, int start_y, char symbol)
		: GameObject(start_x, start_y, symbol), health(h), armor(a), attack(att), faction(f) {
	}

	virtual ~Unit() = default;
	virtual std::unique_ptr<GameObject> clone() const override = 0;

	Faction get_faction() const { return faction; }
	Health get_health_obj() const { return health; }
	Armor get_armor_obj() const { return armor; }
	Attack get_attack_obj() const { return attack; }

	void register_observer(IObserver* observer) {
		if (observer) observers.push_back(observer);
	}

	void take_damage(int damage_amount) {
		health.damage(damage_amount);
		if (health.is_dead()) {
			notify_death();
		}
	}

	// Методы для паттерна Стратегия
	void modify_damage(int amount) {
		int new_dmg = attack.get_damage() + amount;
		attack = Attack(new_dmg < 0 ? 0 : new_dmg);
	}

	void modify_health(int amount) {
		if (amount > 0) health.heal(amount);
		else health.damage(-amount);
		if (health.is_dead()) notify_death();
	}

	friend void operator+(Unit& unit, std::pair<const GoldChest*, Base*> interaction);
	friend void operator-(Unit& unit, const SpikeTrap& trap);
	friend void operator*(Unit& unit, Altar& altar);

private:
	void notify_death() {
		for (auto* obs : observers) {
			if (obs) obs->on_unit_death(this);
		}
	}
};

#include "Base.h" 

inline void operator+(Unit& unit, std::pair<const GoldChest*, Base*> interaction) {
	const GoldChest* chest = interaction.first;
	Base* castle = interaction.second;
	if (chest && castle) {
		std::cout << "[Оператор +] Юнит " << unit.get_type() << " открыл сундук. Ресурсы отправлены в базу " << castle->get_name() << "!\n";
		castle->add_resources(chest->get_loot());
	}
}

inline void operator-(Unit& unit, const SpikeTrap&) {
	std::cout << "[Оператор -] Юнит " << unit.get_type() << " попал в ловушку со шипами!\n";
	unit.take_damage(40);
}

inline void operator*(Unit& unit, Altar& altar) {
	if (altar.strategy) {
		std::cout << "[Оператор *] Юнит " << unit.get_type() << " взаимодействует с объектом типа Altar.\n";
		altar.strategy->apply(unit);
	}
}
