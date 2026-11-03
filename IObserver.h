#pragma once
class Unit;

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void on_unit_death(Unit* dead_unit) = 0;
};
