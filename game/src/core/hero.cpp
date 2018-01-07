#include "hero.h"

#include "equipment_set.h"
#include "equipment.h"

namespace mengde {
namespace core {

Hero::Hero(const HeroTemplate* hero_tpl, uint16_t level)
    : hero_tpl_(hero_tpl),
      equipment_set_(new EquipmentSet(this)),
      level_(level),
      hero_stat_(hero_tpl->GetHeroStat()),
      unit_stat_(),
      xtat_() {
  unit_stat_ = CalcUnitStat();
  xtat_ = CalcHpMp();
  UpdateStat();
}

Hero::~Hero() {
  delete equipment_set_;
}

string Hero::GetId() const {
  return hero_tpl_->GetId();
}

string Hero::GetBitmapPath() const {
  return hero_tpl_->GetBitmapPath();
}

const UnitClass* Hero::GetClass() const {
  return hero_tpl_->GetClass();
}

int Hero::GetClassIndex() const {
  return hero_tpl_->GetClassIndex();
}

int Hero::GetMove() const {
  return hero_tpl_->GetMove();
}

Vec2D* Hero::GetAttackRange() const {
  return hero_tpl_->GetAttackRange();
}

const Attribute& Hero::GetHeroStatBase() const {
  return hero_tpl_->GetHeroStat();
}

void Hero::LevelUp() {
  level_++;
  unit_stat_ = CalcUnitStat();
  xtat_ = CalcHpMp();
}

void Hero::PutOn(const Equipment* equipment) {
  equipment_set_->SetEquipment(equipment);
}

HpMp Hero::CalcHpMp() const {
  HpMp xtat;
#define UPDATE_XTAT(x, xc) xtat.x = GetClass()->GetBni##xc().base + \
                                    GetClass()->GetBni##xc().incr * level_
  UPDATE_XTAT(hp, Hp);
  UPDATE_XTAT(mp, Mp);
#undef UPDATE_XTAT
  return xtat;
}

Attribute Hero::CalcUnitStat() const {
  Attribute unit_stat;
#define UPDATE_STAT(x) unit_stat.x = ((hero_stat_.x / 2) + \
                                      ((100 + 10 * (GetClass()->GetStatGrade()->x - 1)) * level_ * hero_stat_.x) / 2000)
  UPDATE_STAT(atk);
  UPDATE_STAT(def);
  UPDATE_STAT(dex);
  UPDATE_STAT(itl);
  UPDATE_STAT(mor);
#undef UPDATE_STAT
  return unit_stat;
}

void Hero::UpdateStat() {
  unit_stat_ = CalcUnitStat();
  { // FIXME code copied from Unit
    Attribute addends = equipment_set_->CalcAddends();
    Attribute multipliers = equipment_set_->CalcMultipliers();

    for (uint32_t i = 0; i < NUM_STATS; i++) {
      unit_stat_.AddValueByIndex(i, addends.GetValueByIndex(i));
      int val = unit_stat_.GetValueByIndex(i);
      int val_mult = ((100 + multipliers.GetValueByIndex(i)) * val) / 100;
      unit_stat_.SetValueByIndex(i, val_mult);
    }
  }
}

} // namespace core
} // namespace mengde
