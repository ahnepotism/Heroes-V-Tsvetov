#include <iostream>
#include "GameField.h"
#include "UnitFactory.h"

int main() {
    setlocale(LC_ALL, "Russian");

    HavenFactory haven_fab;
    InfernoFactory inferno_fab;
    SylvanFactory sylvan_fab;
    DungeonFactory dungeon_fab;
    AcademyFactory academy_fab;
    NecropolisFactory necropolis_fab;
    StrongholdFactory stronghold_fab;

    std::cout << "СЦЕНАРИЙ 1: Создание поля и наполнение через фабрики\n";
    GameField field1(12, 12, 10);

    field1.add_unit(haven_fab.create_unit(Role::Champion, 0, 0));
    field1.add_unit(inferno_fab.create_unit(Role::Ranged, 3, 1));
    field1.add_unit(sylvan_fab.create_unit(Role::Champion, 11, 11));
    field1.add_unit(dungeon_fab.create_unit(Role::Champion, 5, 5));
    field1.add_unit(academy_fab.create_unit(Role::Champion, 8, 2));
    field1.add_unit(necropolis_fab.create_unit(Role::Ranged, 1, 9));
    field1.add_unit(stronghold_fab.create_unit(Role::Champion, 10, 4));

    std::cout << "Карта игрового мира:\n";
    field1.display();

    std::cout << "СЦЕНАРИЙ 2: Тест Итератора и Боевых Характеристик\n";
    std::cout << "Список существ на поле боя:\n";

    for (const auto& creature : field1) {
        std::cout << " -> [" << creature->get_symbol() << "] " << creature->get_type();
        std::cout << " на позиции (" << creature->get_x() << ", " << creature->get_y() << ")";
        std::cout << " ХП: " << creature->get_health_obj().get_health() << "\n";
    }

    std::cout << "\nСЦЕНАРИЙ 3: Армагеддон (Нанесение массового урона)\n";
    std::cout << "Наносим 150 единиц урона всем мобам на поле\n\n";

    for (auto& creature : field1) {
        creature->take_damage(150);
    }

    field1.remove_dead_units();

    std::cout << "\nПоле боя после Армагеддона:\n";
    field1.display();

    return 0;
}
