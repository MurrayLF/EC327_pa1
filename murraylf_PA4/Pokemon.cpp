#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "Rival.h"
#include "BattleArena.h"

using namespace std;

Pokemon :: Pokemon() : GameObject('P')
{
  health=20;
  store_health=health;
  physical_damage=5;
  magical_damage=4;
  defense=15;
  stamina=20;
  speed=5;
  is_in_gym=false;
  is_in_center=false;
  cout << "Pokemon default constructed" << endl;
}

Pokemon :: Pokemon(char in_code) : GameObject(in_code)
{
  health=20;
  store_health=health;
  physical_damage=5;
  magical_damage=4;
  defense=15;
  stamina=20;
  speed=5;
  is_in_gym=false;
  is_in_center=false;
  cout << "Pokemon constructed" << endl;
  state=STOPPED;
}

Pokemon :: Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) : GameObject(in_loc,in_id,in_code)
{
  health=20;
  store_health=health;
  physical_damage=5;
  magical_damage=4;
  defense=15;
  stamina=20;
  speed=in_speed;
  name=in_name;
  is_in_gym=false;
  is_in_center=false;
  cout << "Pokemon constructed" << endl;
}

Pokemon :: Pokemon(string in_name, double in_speed, double hp, double phys_dmg, double magic_dmg, double def, int in_id, char in_code, Point2D in_loc) : GameObject(in_loc,in_id, in_code)
{
  health=hp;
  store_health=health;
  physical_damage=phys_dmg;
  magical_damage=magic_dmg;
  defense=def;
  stamina=20;
  speed=in_speed;
  name=in_name;
  is_in_gym=false;
  is_in_center=false;
  cout << "Pokemon constructed" << endl;
}

Pokemon :: ~Pokemon()
{
  cout << "Pokemon destructed" << endl;
}

void Pokemon :: StartMoving(Point2D dest)
{
  SetupDestination(dest);
  if (location.x == dest.x && location.y == dest.y)
    cout << display_code << id_num << ": I'm already there. See?" << endl;
  else if (state == EXHAUSTED)
    cout << display_code << id_num << ": I am exhausted. I may move but you cannot see me." << endl;
  else
  {
    state=MOVING;
    cout << display_code << id_num << ": On my way" << endl;
  }
}

void Pokemon :: StartMovingToCenter(PokemonCenter* center)
{
  Point2D loc=center->GetLocation();
  int id=center->GetId();
  if (this->location.x == loc.x && this->location.y == loc.y)
    cout << display_code << id_num << ": I'm already at the Pokemon Center!" << endl;
  else if (state == EXHAUSTED)
    cout << display_code << id_num << ": I am exhausted so I can't move to recover stamina" << endl;
  else
  {
    current_center=center;
    SetupDestination(loc);
    state=MOVING_TO_CENTER;
    cout << display_code << id_num << ": On my way to center " << id << endl;
  }
}

void Pokemon :: StartMovingToGym(PokemonGym* gym)
{
  current_gym=gym;
  Point2D loc=gym->GetLocation();
  int id=gym->GetId();
  if (this->location.x == loc.x && this->location.y == loc.y)
    cout << display_code << id_num << ": I'm already at the Pokemon Gym!" << endl;
  else if (state == EXHAUSTED)
    cout << display_code << id_num << ": I am exhausted so I shouldn't be going to the gym" << endl;
  else
  {
    SetupDestination(loc);
    state=MOVING_TO_GYM;
    cout << display_code << id_num << ": On my way to gym " << id << endl;
  }
}

void Pokemon :: StartTraining(unsigned int num_training_units)
{
  if (state==EXHAUSTED)
  {
    cout << display_code << id_num << ": I am exhausted so no more training for me..." << endl;
  }
  else if (!is_in_gym)
  {
    cout << display_code << id_num << ": I can only train in a Pokemon Gym!" << endl;
  }
  else if (current_gym->IsBeaten())
  {
    cout << display_code << id_num << ": Cannot train! This Pokemon Gym is already beaten!" <<  endl;
  }
  else if (!current_gym->IsAbleToTrain(num_training_units,pokemon_dollars,stamina))
  {
    cout << display_code << id_num << ": Not enough stamina and/or money for training" <<  endl;
  }
  else
  {
    if (num_training_units>current_gym->GetNumTrainingUnitsRemaining())
      training_units_to_buy=current_gym->GetNumTrainingUnitsRemaining();
    else
      training_units_to_buy=num_training_units;
    state=TRAINING_IN_GYM;
    cout << display_code << id_num << ": Started to train at Pokemon Gym " << current_gym->GetId() << " with " << training_units_to_buy << " training units" << endl;
  }
}

void Pokemon :: StartRecoveringStamina(unsigned int num_stamina_points)
{
  if (!is_in_center)
    cout << display_code << id_num << ": I can only recover stamina in a Pokemon Center" << endl;
  else if (abs(current_center->GetDollarCost(num_stamina_points)-pokemon_dollars)>0.01 && pokemon_dollars<current_center->GetDollarCost(num_stamina_points))
    cout << display_code << id_num << ": Not enough money to recover stamina" << endl;
  else if (!(current_center->HasStaminaPoints()))
    cout << display_code << id_num << ": Cannot recover. No stamina points remaining in this Pokemon Center" << endl;
  else
  {
    if (num_stamina_points>current_center->GetNumStaminaPointsRemaining())
      stamina_points_to_buy=current_center->GetNumStaminaPointsRemaining();
    else
      stamina_points_to_buy=num_stamina_points;
    state=RECOVERING_STAMINA;
    cout << display_code << id_num << ": Started recovering " << stamina_points_to_buy << " stamina point(s) at Pokemon Center " << current_center->GetId() << endl;
  }
}

void Pokemon :: Stop()
{
  state=STOPPED;
  cout << display_code << id_num << ": Stopping" << endl;
}

bool Pokemon :: IsExhausted()
{
  if (stamina==0)
    return true;
  else
    return false;
}

bool Pokemon :: ShouldBeVisible()
{
  if (state != EXHAUSTED && state != FAINTED)
    return true;
  else
    return false;
}


void Pokemon :: ShowStatus()
{
  cout << name << " status: ";
  GameObject :: ShowStatus();
  if (state==STOPPED)
    cout << "       " << "stopped" << endl;
  else if (state==MOVING)
    cout << "       " << "moving at speed of " << speed << " to destination " << destination << " at each step of " << delta << endl;
  else if (state==MOVING_TO_CENTER)
    cout << "       " << "heading to Pokemon Center " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
  else if (state==MOVING_TO_GYM)
    cout << "       " << "heading to Pokemon Gym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
    else if (state==MOVING_TO_ARENA)
      cout << "       " << "heading to Battle Arena " << current_arena->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
  else if (state==IN_CENTER)
    cout << "       " << "inside Pokemon Center " << current_center->GetId() << endl;
  else if (state==IN_GYM)
    cout << "       " << "inside Pokemon Gym " << current_gym->GetId() << endl;
    else if (state==IN_ARENA)
      cout << "       " << "inside Battle Arena " << current_arena->GetId() << endl;
  else if (state==TRAINING_IN_GYM)
    cout << "       " << "training in Pokemon Gym " << current_gym->GetId() << endl;
  else if (state==RECOVERING_STAMINA)
    cout << "       " << "recovering stamina in Pokemon Center " << current_center->GetId() << endl;
    else if (state==BATTLE)
      cout << "       " << "battling in Battle Arena " << current_arena->GetId() << endl;

  cout << "       " << "Stamina: " << stamina << endl;
  cout << "       " << "Pokemon Dollars: " << pokemon_dollars << endl;
  cout << "       " << "Experience Points: " << experience_points << endl;
  cout << "       " << "Health: " << health << endl;
  cout << "       " << "Physical Damage: " << physical_damage << endl;
  cout << "       " << "Magical Damage: " << magical_damage << endl;
  cout << "       " << "Defense: " << defense << endl;
}



bool Pokemon :: Update()
{

  bool arrived;
  if (state==STOPPED)
  {
    return false;
  }
  else if (IsExhausted() && state!=EXHAUSTED)
  {
    state=EXHAUSTED;
    cout << name << " is out of stamina and can't move" << endl;
    return false;
  }
  else if (state==MOVING)
  {
    if (is_in_gym)
      current_gym->RemoveOnePokemon();
    if (is_in_center)
      current_center->RemoveOnePokemon();
    is_in_gym=false;
    is_in_center=false;
    arrived=UpdateLocation();
    if (arrived==true)
    {
      state=STOPPED;
      return true;
    }
  }
  else if (state==MOVING_TO_CENTER)
  {
    if (is_in_gym)
      current_gym->RemoveOnePokemon();
    if (is_in_center)
      current_center->RemoveOnePokemon();
    if (is_in_arena)
      current_arena->RemoveOnePokemon();
    is_in_gym=false;
    is_in_center=false;
    is_in_arena=false;

    arrived=UpdateLocation();
    if (arrived==true)
    {
      current_center->AddOnePokemon();
      is_in_center=true;
      state=IN_CENTER;
      return true;
    }
  }
  else if (state==MOVING_TO_GYM)
  {
    if (is_in_gym)
      current_gym->RemoveOnePokemon();
    if (is_in_center)
      current_center->RemoveOnePokemon();
    if (is_in_arena)
      current_arena->RemoveOnePokemon();
    is_in_gym=false;
    is_in_center=false;
    is_in_arena=false;

    arrived=UpdateLocation();
    if (arrived==true)
    {
      current_gym->AddOnePokemon();
      is_in_gym=true;
      state=IN_GYM;
      return true;
    }
  }
  else if (state==MOVING_TO_ARENA)
  {
    if (is_in_gym)
      current_gym->RemoveOnePokemon();
    if (is_in_center)
      current_center->RemoveOnePokemon();
    if (is_in_arena)
      current_arena->RemoveOnePokemon();
    is_in_gym=false;
    is_in_center=false;
    is_in_arena=false;

    arrived=UpdateLocation();
    if (arrived==true)
    {
      current_arena->AddOnePokemon();
      is_in_arena=true;
      state=IN_ARENA;
      return true;
    }
  }
  else if (state==IN_CENTER || state==IN_GYM || state==IN_ARENA)
  {
    return false;
  }
  else if (state==TRAINING_IN_GYM)
  {
    stamina=stamina-current_gym->GetStaminaCost(training_units_to_buy);
    pokemon_dollars=pokemon_dollars-current_gym->GetDollarCost(training_units_to_buy);
    unsigned int exp_gained=current_gym->TrainPokemon(training_units_to_buy);
    experience_points=experience_points+exp_gained;
    cout << "** " << name << " completed " << training_units_to_buy << " training unit(s)! **" << endl;
    cout << "** " << name << " gained " << exp_gained << " experience point(s)! **" << endl;
    state=IN_GYM;
    return true;
  }
  else if (state==RECOVERING_STAMINA)
  {
    unsigned int stamina_gained=current_center->DistributeStamina(stamina_points_to_buy);
    stamina=stamina+stamina_gained;
    pokemon_dollars=pokemon_dollars-current_center->GetDollarCost(stamina_points_to_buy);
    cout << "** " << name << " recovered " << stamina_gained << " stamina point(s)! **" << endl;
    state=IN_CENTER;
    return true;
  }
  else if (state==FAINTED)
  {
    return false;
  }
  else if (state==BATTLE)
  {
    stamina=stamina-current_arena->GetStaminaCost();
    pokemon_dollars=pokemon_dollars-current_arena->GetDollarCost();
    bool win=StartBattle();
    if (win)
    {
      health=store_health;
      state=IN_ARENA;
      target->IsAlive();
    }
    else
    {
      state=FAINTED;
      target->IsAlive();
    }
  }
  return false;
}

bool Pokemon :: UpdateLocation()
{

  if (fabs(destination.x-location.x)<=fabs(delta.x) && fabs(destination.y-location.y)<=fabs(delta.y))
  {
    location=destination;
    cout << display_code << id_num << ": I'm there!"<< endl;
    stamina--;
    pokemon_dollars+=GetRandomAmountOfPokemonDollars();
    return true;
  }
  else
  {
    location=location+delta;
    cout << display_code << id_num << ": step..."<< endl;
    stamina--;
    pokemon_dollars+=GetRandomAmountOfPokemonDollars();
    return false;
  }
}

void Pokemon :: SetupDestination(Point2D dest)
{
  destination=dest;
  delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
}

string Pokemon :: GetName()
{
  return name;
}

bool Pokemon :: IsAlive()
{
  if (state==FAINTED)
    return false;
  else if (health<=0 && state!=FAINTED)
  {
    state=FAINTED;
    return false;
  }
  else
    return true;
}

void Pokemon :: TakeHit(double physic_damage, double magic_damage, double def)
{
  srand(time(NULL));
  int c=rand()%2;
  double damage;
  if (c==0)
  {
    cout << "Ouch, a physical attack!" << endl;
    damage = (100.0-def)/100*physic_damage;
  }
  else
  {
    cout << "Oh no, a magical attack!" << endl;
    damage = (100.0-def)/100*magic_damage;
  }
  health=health-damage;
  cout << "Damage: " << damage <<  endl;
  cout << "Health:" << health << endl;
  cout << "********" << endl;
  return;
}

void Pokemon :: ReadyBattle(Rival* in_target)
{
  if (state!=IN_ARENA)
    cout << display_code << id_num << ": I can only fight in a Battle Arena" << endl;
  else if (state==IN_ARENA && current_arena->IsBeaten()==true)
    cout << display_code << id_num << ": This arena is beaten/unable to fight" << endl;
  else if (state==IN_ARENA && current_arena->IsAbleToFight(pokemon_dollars,stamina)==false)
    cout << display_code << id_num << ": Inadequate pokemon dollars/stamina" << endl;
  else if (state==IN_ARENA && in_target->IsAlive()==false)
    cout << display_code << id_num << ": This rival has already been defeated" << endl;
  else if (state==IN_ARENA && current_arena->IsAbleToFight(pokemon_dollars,stamina)==true && current_arena->IsBeaten()==false && in_target->IsAlive()==true)
  {
    cout << display_code << id_num << ": Get ready for the battle" << endl;
    target=in_target;
    state=BATTLE;
  }
  else
  {
    state=IN_ARENA;
  }
}

bool Pokemon :: StartBattle()
{
  int round_num=0;
  while (this->IsAlive() && target->IsAlive())
  {
    if (round_num%2==0)
      this->TakeHit(target->get_phys_dmg(),target->get_magic_dmg(),target->get_defense());
    else
      target->TakeHit(physical_damage,magical_damage,defense);
    round_num++;
  }
  if (this->IsAlive())
    {
      cout << "Congratulations, you have beaten this rival" << endl;
      current_arena->RemoveOneRival();
      return true;
    }
  else
    {
      cout << "Condolences, " << name << " has been defeated" << endl;
      current_arena->RemoveOnePokemon();
      return false;
    }
}

void Pokemon :: StartMovingToArena(BattleArena * arena)
{
  current_arena=arena;
  Point2D loc=arena->GetLocation();
  int id=arena->GetId();
  if (this->location.x == loc.x && this->location.y == loc.y)
    cout << display_code << id_num << ": I'm already at the Pokemon Arena!" << endl;
  else if (state == EXHAUSTED)
    cout << display_code << id_num << ": I am exhausted so I shouldn't be going to the arena" << endl;
  else
  {
    SetupDestination(loc);
    state=MOVING_TO_ARENA;
    cout << display_code << id_num << ": On my way to arena " << id << endl;
  }
}

double GetRandomAmountOfPokemonDollars()
{
  srand(time(NULL));
  return rand()%20/10.0;
}
