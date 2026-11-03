#include <iostream>
#include <windows.h>
#include <vector>
#include <memory>
#include <conio.h> 
#include <string>
#include "GameField.h"
#include "UnitFactory.h"
#include "Terrain.h"
#include "NeutralObject.h"
#include "Base.h"

void run_scenario_1();
void run_scenario_2();
void run_scenario_3();
void run_scenario_4();

int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    setlocale(LC_ALL, "Russian");

    int choice = 0;
    while (true) {
        system("cls");
        std::cout << "Выберите сценарий для запуска:\n";
        std::cout << "1. Тест Паттерна [Наблюдатель] (Лимиты базы и авто-очистка)\n";
        std::cout << "2. Тест Паттерна [Прокси] (Логирование проходимости и левитация)\n";
        std::cout << "3. Тест [Перегрузки операторов] и [Стратегии] (Сундуки, Ловушки, Алтари)\n";
        std::cout << "4. Ручное управление юнитом WASD на карте 15 на 15\n";
        std::cout << "5. Выход из программы\n";
        std::cout << "\n";
        std::cout << "Введите номер (1-5): ";
        std::cin >> choice;

        if (choice == 1)      run_scenario_1();
        else if (choice == 2) run_scenario_2();
        else if (choice == 3) run_scenario_3();
        else if (choice == 4) run_scenario_4();
        else if (choice == 5) break;

        std::cout << "\nНажмите любую клавишу для возврата в главное меню...";
        _getch();
    }

    return 0;
}

void run_scenario_1() {
    system("cls");
    std::cout << "Сценарий 1: Тестирование работы Наблюдателя и лимитов гарнизона ---\n\n";

    HavenFactory haven_fab;
    Base haven_castle("Грифонхолд", Faction::Haven, 2);
    haven_castle.print_status();

    GameField battlefield(5, 5, 10);

    std::cout << "[Действие] Нанимаем первого воина (Squire)...\n";
    std::unique_ptr<Unit> squire = haven_fab.create_unit(Role::Standard, 0, 0);
    if (haven_castle.can_recruit() && squire) {
        haven_castle.register_new_unit(squire.get());
        battlefield.add_unit(std::move(squire));
    }

    std::cout << "[Действие] Нанимаем второго воина (Marksman)...\n";
    std::unique_ptr<Unit> marksman = haven_fab.create_unit(Role::Ranged, 1, 0);
    if (haven_castle.can_recruit() && marksman) {
        haven_castle.register_new_unit(marksman.get());
        battlefield.add_unit(std::move(marksman));
    }
    haven_castle.print_status();

    std::cout << "[Тест лимита] Попытка нанять 3-го юнита при лимите базы 2:\n";
    if (!haven_castle.can_recruit()) {
        std::cout << ">> \033[1;31mДействие заблокировано системой:\033[0m В замке Грифонхолд нет мест!\n\n";
    }

    std::cout << "[Бой] Наш Squire на позиции (0,0) получает критический смертельный урон (300 HP)...\n";
    Unit* test_unit = battlefield.get_unit_ptr_by_coords(0, 0);
    if (test_unit) {
        test_unit->take_damage(300);
    }

    std::cout << "\n[Результат работы паттерна Наблюдатель]:\n";
    haven_castle.print_status();
}


void run_scenario_2() {
    system("cls");
    std::cout << "Сценарий 2: Проверка Ландшафтов и Паттерна Прокси ---\n\n";

    auto swamp = std::make_shared<Swamp>();
    auto plain = std::make_shared<Plain>();

    TerrainProxy swamp_proxy(swamp);
    TerrainProxy plain_proxy(plain);

    std::cout << "[Тест Прокси] Проверяем штраф скорости фракции Инферно на Болоте:\n";
    double speed_inferno = swamp_proxy.get_speed_modifier(Faction::Inferno);
    std::cout << ">> Модификатор скорости Демонов на Болоте: " << speed_inferno << " (Вязнут в тине)\n\n";

    std::cout << "[Тест Прокси] Проверяем проходимость болота для левитирующих магов Академии:\n";
    if (swamp_proxy.is_passable(Faction::Academy)) {
        std::cout << ">> \033[1;32mПрокси разрешил проход:\033[0m Юниты Академии левитируют, болото игнорируется!\n\n";
    }

    std::cout << "[Тест Прокси] Проверяем проходимость болота для обычных рыцарей Haven:\n";
    swamp_proxy.is_passable(Faction::Haven);
}

void run_scenario_3() {
    system("cls");
    std::cout << "--- СЦЕНАРИЙ 3: Взаимодействие объектов через Операторы и Стратегии ---\n\n";

    HavenFactory haven_fab;
    DungeonFactory dungeon_fab;
    Base haven_castle("Грифонхолд", Faction::Haven, 5);

    std::unique_ptr<Unit> squire = haven_fab.create_unit(Role::Standard, 0, 0);
    std::unique_ptr<Unit> raider = dungeon_fab.create_unit(Role::Standard, 0, 0);

    GoldChest chest(0, 0);
    SpikeTrap trap(0, 0);
    Altar altar_atk(0, 0, std::make_unique<AttackBoostStrategy>());

    std::cout << "=== 1. ТЕСТ ОПЕРАТОРА + (Сбор ресурсов в Замок напрямую) ===\n";
    haven_castle.print_status();
    if (squire) {
        *squire + std::make_pair(&chest, &haven_castle);
    }
    haven_castle.print_status();

    std::cout << "\n=== 2. ТЕСТ ОПЕРАТОРА - (Ловушка со шипами) ===\n";
    if (squire) {
        std::cout << "ХП Сквайра ДО ловушки: " << squire->get_health_obj().get_health() << "\n";
        *squire - trap;
        std::cout << "ХП Сквайра ПОСЛЕ ловушки: " << squire->get_health_obj().get_health() << "\n";
    }

    std::cout << "\n=== 3. ТЕСТ ОПЕРАТОРА * И ПАТТЕРНА СТРАТЕГИЯ (Бафф фракции) ===\n";
    if (raider) {
        std::cout << "Атака Наездника ДО Алтаря: " << raider->get_attack_obj().get_damage() << "\n";
        *raider* altar_atk;
        std::cout << "Атака Наездника ПОСЛЕ Алтаря (Dungeon получает +30!): " << raider->get_attack_obj().get_damage() << "\n";
    }
}
    void run_scenario_4() {
        system("cls");
        std::cout << "=========================================================\n";
        std::cout << "      ИНТЕРАКТИВНЫЙ РЕЖИМ УПРАВЛЕНИЯ ЮНИТОМ (ЛАБА №2)     \n";
        std::cout << "=========================================================\n\n";

        std::cout << "Выберите фракцию для игры:\n";
        std::cout << "1. Order of Heaven (Haven)\n2. League of Shadows (Dungeon)\n3. Inferno Legions (Inferno)\n4. Sylvan Woods (Sylvan)\n5. Silver Academy (Academy)\n6. Necropolis Undead (Necropolis)\n7. Orcish Stronghold (Stronghold)\n";
        std::cout << "Введите номер фракции (1-7): ";
        int faction_choice = 1;
        std::cin >> faction_choice;

        Faction player_faction = Faction::Haven;
        std::unique_ptr<UnitFactory> factory;
        std::string castle_name = "Грифонхолд";

        switch (faction_choice) {
        case 2: player_faction = Faction::Dungeon; factory = std::make_unique<DungeonFactory>(); castle_name = "Тёмный Рубеж"; break;
        case 3: player_faction = Faction::Inferno; factory = std::make_unique<InfernoFactory>(); castle_name = "Шеол"; break;
        case 4: player_faction = Faction::Sylvan; factory = std::make_unique<SylvanFactory>(); castle_name = "Сайрис Тилл"; break;
        case 5: player_faction = Faction::Academy; factory = std::make_unique<AcademyFactory>(); castle_name = "Серебряные Города"; break;
        case 6: player_faction = Faction::Necropolis; factory = std::make_unique<NecropolisFactory>(); castle_name = "Насхир"; break;
        case 7: player_faction = Faction::Stronghold; factory = std::make_unique<StrongholdFactory>(); castle_name = "Племя Клыка"; break;
        default: player_faction = Faction::Haven; factory = std::make_unique<HavenFactory>(); castle_name = "Грифонхолд"; break;
        }

        std::cout << "\n--- Доступные рекруты в замке " << castle_name << " ---\n";
        switch (player_faction) {
        case Faction::Haven:      std::cout << "1. Squire (Пехотинец)\n2. Marksman (Стрелок)\n3. Archangel (Чемпион)\n"; break;
        case Faction::Dungeon:    std::cout << "1. Assassin (Пехотинец)\n2. Dark Raider (Наездник)\n3. Shadow Dragon (Чемпион)\n"; break;
        case Faction::Inferno:    std::cout << "1. Horned Demon (Пехотинец)\n2. Succubus (Стрелок)\n3. Archdevil (Чемпион)\n"; break;
        case Faction::Sylvan:     std::cout << "1. Pixie (Пехотинец)\n2. Master Hunter (Стрелок)\n3. Green Dragon (Чемпион)\n"; break;
        case Faction::Academy:    std::cout << "1. Gremlin (Пехотинец)\n2. Mage (Маг/Стрелок)\n3. Colossus (Чемпион)\n"; break;
        case Faction::Necropolis: std::cout << "1. Skeleton (Пехотинец)\n2. Lich (Стрелок)\n3. Bone Dragon (Чемпион)\n"; break;
        case Faction::Stronghold: std::cout << "1. Goblin (Пехотинец)\n2. Orc Warrior (Стрелок)\n3. Cyclops (Чемпион)\n"; break;
        }

        std::cout << "Выберите воина для найма (1-3): ";
        int role_choice = 1;
        std::cin >> role_choice;

        Role unit_role = Role::Standard;
        if (role_choice == 2) unit_role = Role::Ranged;
        else if (role_choice == 3) unit_role = Role::Champion;

        const int MAP_SIZE = 15;
        GameField battlefield(MAP_SIZE, MAP_SIZE, 100);
        Base player_castle(castle_name, player_faction, 5, 0, 0);

        std::vector<std::vector<std::shared_ptr<Terrain>>> map_terrain(MAP_SIZE, std::vector<std::shared_ptr<Terrain>>(MAP_SIZE));
        for (int y = 0; y < MAP_SIZE; ++y) {
            for (int x = 0; x < MAP_SIZE; ++x) {
                if (y >= 3 && y <= 7 && x >= 4 && x <= 12)                 map_terrain[y][x] = std::make_shared<Forest>();
                else if (y >= 10 && y <= 14 && x >= 6 && x <= 16)           map_terrain[y][x] = std::make_shared<Swamp>();
                else if (y >= 13 && x <= 5)                                map_terrain[y][x] = std::make_shared<Underworld>();
                else                                                       map_terrain[y][x] = std::make_shared<Plain>();
            }
        }

        battlefield.add_unit(std::make_unique<GoldChest>(5, 2));
        battlefield.add_unit(std::make_unique<GoldChest>(12, 12));
        battlefield.add_unit(std::make_unique<SpikeTrap>(4, 5));
        battlefield.add_unit(std::make_unique<SpikeTrap>(11, 10));
        battlefield.add_unit(std::make_unique<SpikeTrap>(9, 12));
        battlefield.add_unit(std::make_unique<SpikeTrap>(5, 5));
        battlefield.add_unit(std::make_unique<Altar>(8, 4, std::make_unique<AttackBoostStrategy>()));
        battlefield.add_unit(std::make_unique<Altar>(14, 13, std::make_unique<HealthRestoreStrategy>()));

        int current_x = 1;
        int current_y = 0;
        std::unique_ptr<Unit> my_creature = factory->create_unit(unit_role, current_x, current_y);

        if (my_creature) {
            player_castle.register_new_unit(my_creature.get());
            battlefield.add_unit(std::move(my_creature));
        }

        std::cout << "\nПоле боя сгенерировано. Управление: W, A, S, D. Выход в меню — Q.\n";
        std::cout << "Нажмите любую клавишу для входа на карту...";
        _getch();

        char key = ' ';
        std::string event_message = "Вы вошли на карту. Исследуйте территорию!";

        while (key != 'q' && key != 'Q') {
            system("cls");
            player_castle.print_status();

            Unit* my_unit_ptr = nullptr;
            for (auto& obj : battlefield) {
                Unit* u = dynamic_cast<Unit*>(&obj);
                if (u && u->get_x() == current_x && u->get_y() == current_y) {
                    my_unit_ptr = u;
                    break;
                }
            }

            std::cout << "Статус Вашего Воина" << "\n";
            std::cout << "Координаты на карте: (" << current_x << ", " << current_y << ")\n";

            if (my_unit_ptr) {
                int current_hp = my_unit_ptr->get_health_obj().get_health();
                int current_dmg = my_unit_ptr->get_attack_obj().get_damage();

                if (current_hp <= 0) {
                    std::cout << "\033[1;31mСОСТОЯНИЕ: ПОГИБ В БОЮ (Здоровье: 0)\033[0m\n";
                    event_message = "\033[1;31m[КРИТИЧЕСКИЙ ЛОГ] Ваш юнит пал смертью храбрых!\033[0m";
                }
                else {
                    std::cout << "Здоровье: \033[1;32m" << current_hp << "\033[0m ХП\n";
                    std::cout << "Атака: \033[1;33m" << current_dmg << "\033[0m единиц\n";
                }
            }
            else {
                std::cout << "\033[1;31mЮнит не найден на поле боя (возможно, он погиб)\033[0m\n";
            }

            TerrainProxy cell_proxy(map_terrain[current_y][current_x]);
            double speed = cell_proxy.get_speed_modifier(player_faction);
            std::cout << "Эффект Прокси: Скорость фракции на текущей плитке = " << speed << "\n";
            std::cout << "\033[1;95mПоследнее событие:\033[0m " << event_message << "\n\n";

            battlefield.display(map_terrain, player_castle);

            if (my_unit_ptr && my_unit_ptr->get_health_obj().get_health() <= 0) {
                std::cout << "Нажмите 'Q' для выхода в меню...\n";
                do { key = _getch(); } while (key != 'q' && key != 'Q');
                break;
            }

            key = _getch();
            int next_x = current_x; int next_y = current_y;
            if (key == 'w' || key == 'W') next_y--;
            if (key == 's' || key == 'S') next_y++;
            if (key == 'a' || key == 'A') next_x--;
            if (key == 'd' || key == 'D') next_x++;

            if (next_x != current_x || next_y != current_y) {
                if (next_x >= 0 && next_x < MAP_SIZE && next_y >= 0 && next_y < MAP_SIZE) {
                    int real_index = battlefield.find_unit_index_by_coords(current_x, current_y);
                    if (real_index != -1) {
                        int hp_before = (my_unit_ptr) ? my_unit_ptr->get_health_obj().get_health() : 0;
                        int dmg_before = (my_unit_ptr) ? my_unit_ptr->get_attack_obj().get_damage() : 0;

                        battlefield.move_unit(static_cast<size_t>(real_index), next_x, next_y, &player_castle);
                        current_x = next_x; current_y = next_y;
                        Unit* updated_unit = nullptr;
                        for (auto& obj : battlefield) {
                            Unit* u = dynamic_cast<Unit*>(&obj);
                            if (u && u->get_x() == current_x && u->get_y() == current_y) {
                                updated_unit = u;
                                break;
                            }
                        }

                        if (updated_unit) {
                            int hp_after = updated_unit->get_health_obj().get_health();
                            int dmg_after = updated_unit->get_attack_obj().get_damage();

                            if (hp_after < hp_before)
                                event_message = "\033[1;31m[ЛОКАЦИЯ] Юнит наступил на ловушку с шипами (^) и потерял " + std::to_string(hp_before - hp_after) + " ХП!\033[0m";
                            else if (hp_after > hp_before)
                                event_message = "\033[1;32m[АЛТАРЬ] Юнит активировал Источник Живой Воды! Восстановлено +" + std::to_string(hp_after - hp_before) + " ХП.\033[0m";
                            else if (dmg_after > dmg_before)
                                event_message = "\033[1;36m[АЛТАРЬ] Юнит посетил Алтарь Силы! Атака выросла на +" + std::to_string(dmg_after - dmg_before) + " ед.!\033[0m";
                            else
                                event_message = "Юнит перешел в клетку (" + std::to_string(current_x) + ", " + std::to_string(current_y) + ").";
                        }
                    }
                }
            }
        }
    }


