#include "Strategy.h"
#include "Unit.h"
#include <iostream>

void AttackBoostStrategy::apply(Unit& unit) {
    if (unit.get_faction() == Faction::Dungeon) {
        unit.modify_damage(30);
        std::cout << "[Стратегия] Юнит Лиги Теней получает максимальный бафф Алтаря Силы! Атака +30.\n";
    }
    else {
        unit.modify_damage(10);
        std::cout << "[Стратегия] Алтарь Силы увеличивает атаку юнита на 10.\n";
    }
}

void HealthRestoreStrategy::apply(Unit& unit) {
    if (unit.get_faction() == Faction::Necropolis || unit.get_faction() == Faction::Inferno) {
        unit.modify_health(-20);
        std::cout << "[Стратегия] Живая вода Источника Энергии обжигает нежить/демона! Нанесено 20 урона.\n";
    }
    else {
        unit.modify_health(50);
        std::cout << "[Стратегия] Источник Энергии восстанавливает юниту 50 единиц здоровья.\n";
    }
}

void ManaBoostStrategy::apply(Unit& unit) {
    if (unit.get_faction() == Faction::Academy) {
        unit.modify_damage(15);
        std::cout << "[Стратегия] Маг Академии резонирует с объектом! Получен бафф к магии/атаке +15.\n";
    }
    else {
        std::cout << "[Стратегия] Объект нейтрален к данному типу юнита. Эффект отсутствует.\n";
    }
}
