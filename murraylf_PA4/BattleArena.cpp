#include <iostream>
#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"
#include "BattleArena.h"

BattleArena :: BattleArena()
{
  display_code='A';
  pokemon_count=0;
  max_num_rivals=3;
  num_rivals_remaining=max_num_rivals;
  dollar_cost_per_fight=4;
  stamina_cost_per_fight=3;
  state=RIVALS_AVAILABLE;
  cout << "BattleArena default constructed" << endl;
}

BattleArena :: BattleArena(unsigned int max_rivals, unsigned int stamina_cost, double dollar_cost, int in_Id, Point2D in_loc) : Building('A', in_Id, in_loc)
{
  pokemon_count=0;
  max_num_rivals=max_rivals;
  num_rivals_remaining=max_num_rivals;
  dollar_cost_per_fight=dollar_cost;
  stamina_cost_per_fight=stamina_cost;
  state=RIVALS_AVAILABLE;
  cout << "BattleArena constructed" << endl;
}

BattleArena :: ~BattleArena()
{
  cout << "BattleArena destructed" << endl;
}

unsigned int BattleArena :: GetNumRivalsRemaining()
{
  return num_rivals_remaining;
}

bool BattleArena :: HasEnoughRivals()
{
  if (num_rivals_remaining>=1)
    return true;
  else
    return false;
}

double BattleArena :: GetDollarCost()
{
  return dollar_cost_per_fight;
}

unsigned int BattleArena :: GetStaminaCost()
{
  return stamina_cost_per_fight;
}

bool BattleArena :: IsAbleToFight(double budget, unsigned int stamina)
{
  if (budget>=dollar_cost_per_fight && stamina>=stamina_cost_per_fight)
    return true;
  else
    return false;
}

bool BattleArena :: Update()
{
  if (state==RIVALS_AVAILABLE)
    return false;
  else if (state!=NO_RIVALS_AVAILABLE && IsBeaten()==true)
  {
    state=NO_RIVALS_AVAILABLE;
    return true;
  }
  return false;
}

bool BattleArena :: IsBeaten()
{
  if (num_rivals_remaining==0)
    return true;
  else
    return false;
}

void BattleArena :: ShowStatus()
{
  cout << "Battle Arena Status: ";
  Building :: ShowStatus();

  cout << "       " << "Max number of rivals: " << max_num_rivals << endl;
  cout << "       " << "Stamina cost per fight: " << stamina_cost_per_fight << endl;
  cout << "       " << "Pokemon dollars cost per fight: " << dollar_cost_per_fight << endl;
  cout << "       " << num_rivals_remaining << " rival(s) are remaining for this arena" << endl;
}

void BattleArena :: RemoveOneRival()
{
  //Removes one rival from a given arena
  if (num_rivals_remaining != 0)
    num_rivals_remaining--;
  return;
}

void BattleArena :: AddOneRival()
{
  //Adds one rival to a given arena
  max_num_rivals++;
  num_rivals_remaining++;
  return;
}
