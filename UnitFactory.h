#pragma once

#include <memory>
#include "Unit.h"
#include "Units.h"

enum class Role {Standard, Ranged, Champion};

class UnitFactory {
public:
	virtual ~UnitFactory() = default;
	virtual std::unique_ptr<Unit> create_unit(Role role, int x, int y) const = 0;
};

// Фабрика Ордена Порядка

class HavenFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> create_unit(Role role, int x, int y) const override {
        if (role == Role::Standard) return std::make_unique<Squire>(x, y);
        if (role == Role::Ranged)   return std::make_unique<Marksman>(x, y);
        if (role == Role::Champion) return std::make_unique<Archangel>(x, y);
        return nullptr;
    }
};

// Фабрика Инферно

class InfernoFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> create_unit(Role role, int x, int y) const override {
        if (role == Role::Standard) return std::make_unique<HornedOverseer>(x, y);
        if (role == Role::Ranged)   return std::make_unique<SuccubusMistress>(x, y);
        if (role == Role::Champion) return std::make_unique<ArchDevil>(x, y);
        return nullptr;
    }
};

// Фабрика Лесного Союза

class SylvanFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> create_unit(Role role, int x, int y) const override {
        if (role == Role::Standard) return std::make_unique<BladeSinger>(x, y);
        if (role == Role::Ranged)   return std::make_unique<MasterBowman>(x, y);
        if (role == Role::Champion) return std::make_unique<EmeraldDragon>(x, y);
        return nullptr;
    }
};

// Фабрика Лиги Теней

class DungeonFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> create_unit(Role role, int x, int y) const override {
        if (role == Role::Standard) return std::make_unique<BloodMaiden>(x, y);
        if (role == Role::Ranged)   return std::make_unique<DarkRaider>(x, y);
        if (role == Role::Champion) return std::make_unique<BlackDragon>(x, y);
        return nullptr;
    }
};

// Фабрика Магической Академии

class AcademyFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> create_unit(Role role, int x, int y) const override {
        if (role == Role::Standard) return std::make_unique<IronGolem>(x, y);
        if (role == Role::Ranged)   return std::make_unique<ArchMage>(x, y);
        if (role == Role::Champion) return std::make_unique<Titan>(x, y);
        return nullptr;
    }
};

// Фабрика Некромантов

class NecropolisFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> create_unit(Role role, int x, int y) const override {
        if (role == Role::Standard) return std::make_unique<SkeletonWarrior>(x, y);
        if (role == Role::Ranged)   return std::make_unique<LichMaster>(x, y);
        if (role == Role::Champion) return std::make_unique<SpectralDragon>(x, y);
        return nullptr;
    }
};

// Фабрика Великой Орды

class StrongholdFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> create_unit(Role role, int x, int y) const override {
        if (role == Role::Standard) return std::make_unique<OrcWarrior>(x, y);
        if (role == Role::Ranged)   return std::make_unique<CentaurMarauder>(x, y);
        if (role == Role::Champion) return std::make_unique<UntamedCyclops>(x, y);
        return nullptr;
    }
};