#ifndef RIVAL_H
#define RIVAL_H

#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"
#include "BattleArena.h"

enum RivalStates{
  ALIVE_RIVAL=0,
  FAINTED_RIVAL=1
};

class Rival : public GameObject
{
protected:
  double speed;
  string name;
  double health;
  double physical_damage;
  double magical_damage;
  double defense;
  double stamina_cost_per_fight;
  bool is_in_arena;
  BattleArena * current_arena;
public:
  Rival(string name, double speed, double hp, double phys_dmg,double magic_dmg, double def, int id, Point2D in_loc);
  ~Rival();
  void TakeHit(double physic_damage, double magic_damage, double def);
  double get_phys_dmg();
  double get_magic_dmg();
  double get_defense();
  double get_health();
  bool Update();
  void ShowStatus();
  bool IsAlive();
  bool ShouldBeVisible();
  void SetArena(BattleArena * arena);
};

#endif
