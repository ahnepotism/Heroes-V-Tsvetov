#pragma once

#include "Unit.h"

// Орден порядка
class HeavenUnit : public Unit {
public:
	using Unit::Unit;
	std::string get_type() const override { return "Haven"; }
};

class Squire : public HeavenUnit {
public:
	Squire(int x, int y) : HeavenUnit(Health(120), Armor(30), Attack(12), x, y, 'Л') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<Squire>(*this); }
	std::string get_type() const override { return "Squire (Haven)"; }
};
class Marksman : public HeavenUnit {
public:
	Marksman(int x, int y) : HeavenUnit(Health(75), Armor(12), Attack(24), x, y, 'Б') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<Marksman>(*this); }
	std::string get_type() const override { return "Marksman (Haven)"; }
};
class Archangel : public HeavenUnit {
public:
	Archangel(int x, int y) : HeavenUnit(Health(250), Armor(45), Attack(40), x, y, 'А'){}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<Archangel>(*this); }
	std::string get_type() const override { return "Archangel (Haven)"; }
};

// Инферно

class InfernoUnit : public Unit {
public:
	using Unit::Unit;
	std::string get_type() const override { return "Infetno"; }
};

class HornedOverseer : public InfernoUnit {
public:
	HornedOverseer(int x, int y) : InfernoUnit(Health(130), Armor(10), Attack(16), x, y, 'Р') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<HornedOverseer>(*this); }
	std::string get_type() const override { return "Horned Overseer (Inferno)"; }
};
class SuccubusMistress : public InfernoUnit {
public:
	SuccubusMistress(int x, int y) : InfernoUnit(Health(80), Armor(8), Attack(28), x, y, 'С') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<SuccubusMistress>(*this); }
	std::string get_type() const override { return "Succubus Mistress (Inferno)"; }
};
class ArchDevil : public InfernoUnit {
public:
	ArchDevil(int x, int y) : InfernoUnit(Health(230), Armor(30), Attack(45), x, y, 'Д') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<ArchDevil>(*this); }
	std::string get_type() const override { return "ArchDevil (Inferno)"; }
};

// Лесной Союз

class SylvanUnit : public Unit {
public:
	using Unit::Unit;
	std::string get_type() const override { return "Sylvan"; }
};

class BladeSinger : public SylvanUnit {
public:
	BladeSinger(int x, int y) : SylvanUnit(Health(90), Armor(15), Attack(20), x, y, 'Т') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<BladeSinger>(*this); }
	std::string get_type() const override { return "Blade Singer (Sylvan)"; }
};
class MasterBowman : public SylvanUnit {
public:
	MasterBowman(int x, int y) : SylvanUnit(Health(70), Armor(6), Attack(32), x, y, 'М') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<MasterBowman>(*this); }
	std::string get_type() const override { return "Master Bowman (Sylvan)"; }
};
class EmeraldDragon : public SylvanUnit {
public:
	EmeraldDragon(int x, int y) : SylvanUnit(Health(240), Armor(35), Attack(42), x, y, 'Э') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<EmeraldDragon>(*this); }
	std::string get_type() const override { return "Emerald Dragon (Sylvan)"; }
};

// Лига Теней

class DungeonUnit : public Unit {
public:
	using Unit::Unit;
	std::string get_type() const override { return "Dungeon"; }
};

class BloodMaiden : public DungeonUnit {
public:
	BloodMaiden(int x , int y) : DungeonUnit(Health(85), Armor(5), Attack(24), x, y, 'К') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<BloodMaiden>(*this); }
	std::string get_type() const override { return "Blood Maiden (Dungeon)"; }
};
class DarkRaider : public DungeonUnit {
public:
	DarkRaider(int x, int y) : DungeonUnit(Health(95), Armor(14), Attack(26), x, y, 'Я') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<DarkRaider>(*this); }
	std::string get_type() const override { return "Dark Raider (Dungeon)"; }
};
class BlackDragon : public DungeonUnit {
public:
	BlackDragon(int x, int y ) : DungeonUnit(Health(260), Armor(40), Attack(48), x, y, 'Ё') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<BlackDragon>(*this); }
	std::string get_type() const override { return "Black Dragon (Dungeon)"; }
};

// Магическая Академия 

class AcademyUnit : public Unit {
public:
	using Unit::Unit;
	std::string get_type() const override { return "Academy"; }
};

class IronGolem : public AcademyUnit {
public:
	IronGolem(int x, int y) : AcademyUnit(Health(160), Armor(35), Attack(10), x, y, 'Г') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<IronGolem>(*this); }
	std::string get_type() const override { return "Iron Golem (Academy)"; }
};
class ArchMage : public AcademyUnit {
public:
	ArchMage(int x, int y) : AcademyUnit(Health(90), Armor(15), Attack(30), x, y, 'Х') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<ArchMage>(*this); }
	std::string get_type() const override { return "Arch Mage (Academy)"; }
	
};
class Titan : public AcademyUnit {
public:
	Titan(int x, int y) : AcademyUnit(Health(270), Armor(40), Attack(40), x, y, 'И') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<Titan>(*this); }
	std::string get_type() const override { return "Titan (Academy)"; }
};

// Некроманты

class NecropolisUnit : public Unit {
public:
	using Unit::Unit;
	std::string get_type() const override { return "Necropolis"; }
};

class SkeletonWarrior : public NecropolisUnit {
public:
	SkeletonWarrior(int x, int y) : NecropolisUnit(Health(75), Armor(15), Attack(10), x, y, 'С') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<SkeletonWarrior>(*this); }
	std::string get_type() const override { return "Skeleton Warrior (Necropolis)"; }
};
class LichMaster : public NecropolisUnit {
public:
	LichMaster(int x, int y) : NecropolisUnit(Health(110), Armor(18), Attack(25), x, y, 'Ч') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<LichMaster>(*this); }
	std::string get_type() const override { return "Lich Master (Necropolis)"; }
};
class SpectralDragon : public NecropolisUnit {
public:
	SpectralDragon(int x, int y) : NecropolisUnit(Health(220), Armor(30), Attack(38), x, y, 'Е') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<SpectralDragon>(*this); }
	std::string get_type() const override { return "Spectral Dragon (Necropolis)"; }
};

// Орда Орков

class StrongholdUnit : public Unit {
public:
	using Unit::Unit;
	std::string get_type() const override { return "Stronghold"; }
};

class OrcWarrior : public StrongholdUnit {
public:
	OrcWarrior(int x, int y) : StrongholdUnit(Health(140), Armor(12), Attack(18), x, y, 'О') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<OrcWarrior>(*this); }
	std::string get_type() const override { return "Orc Warrior (Stronghold)"; }
};
class CentaurMarauder : public StrongholdUnit {
public:
	CentaurMarauder(int x, int y) : StrongholdUnit(Health(95), Armor(10), Attack(22), x, y, 'В') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<CentaurMarauder>(*this); }
	std::string get_type() const override { return "Centaur Marauder (Stronghold)"; }
};
class UntamedCyclops : public StrongholdUnit {
public:
	UntamedCyclops(int x, int y) : StrongholdUnit(Health(300), Armor(25), Attack(50), x, y, 'Ц') {}
	std::unique_ptr<Unit> clone() const override { return std::make_unique<UntamedCyclops>(*this); }
	std::string get_type() const override { return "Untamed Cyclops (Stronghold)"; }
};
