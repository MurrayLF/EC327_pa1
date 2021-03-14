#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"
#include "BattleArena.h"
#include "Rival.h"

Rival :: Rival(string in_name, double in_speed, double hp, double phys_dmg,double magic_dmg, double def, int id, Point2D in_loc) : GameObject(in_loc, id, 'R')
{
  speed=in_speed;
  name=in_name;
  health=hp;
  physical_damage=phys_dmg;
  magical_damage=magic_dmg;
  defense=def;
  is_in_arena=true;
  state=ALIVE_RIVAL;
}

Rival :: ~Rival()
{
  cout << "Rival destructed" << endl;
}

void Rival :: TakeHit(double physic_damage, double magic_damage, double def)
{
  srand(time(NULL));
  int c=rand()%2;
  double damage;
  if (c==0)
    damage = (100.0-def)/100*physic_damage;
  else
    damage = (100.0-def)/100*magic_damage;
  health=health-damage;
  return;
}

double Rival :: get_phys_dmg()
{
  return physical_damage;
}

double Rival :: get_magic_dmg()
{
  return magical_damage;
}

double Rival :: get_defense()
{
  return defense;
}

double Rival :: get_health()
{
  return health;
}

bool Rival :: ShouldBeVisible()
{
  if (state != FAINTED_RIVAL)
    return true;
  else
    return false;
}

bool Rival :: Update()
{
  if (state==ALIVE_RIVAL && health>0)
    return false;
  else if (state==FAINTED_RIVAL)
    return false;
  return false;
}

void Rival :: ShowStatus()
{
  cout << name << " status: ";
  GameObject :: ShowStatus();

  if (state==ALIVE_RIVAL)
    cout << "       " << "alive" << endl;
  else if (state==FAINTED_RIVAL)
    cout << "       " << "fainted" << endl;

  cout << "       " << "Health: " << health << endl;
  cout << "       " << "Physical Damage: " << physical_damage << endl;
  cout << "       " << "Magical Damage: " << magical_damage << endl;
  cout << "       " << "Defense: " << defense << endl;
}

bool Rival :: IsAlive()
{
  if (state==FAINTED_RIVAL)
    return false;
  else if (health<=0 && state!=FAINTED_RIVAL)
  {
    state=FAINTED_RIVAL;
    return false;
  }
  else
    return true;
}

void Rival :: SetArena(BattleArena * arena)
{
  current_arena=arena;
}
