#ifndef MODEL_H
#define MODEL_H

#include <list>
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "BattleArena.h"
#include "Rival.h"
#include "View.h"


class Model
{
private:
  int tick;
  list <GameObject *> object_ptrs;
  list <GameObject *> active_ptrs;
  list <Pokemon *> pokemon_ptrs;
  list <PokemonGym *> gym_ptrs;
  list <PokemonCenter *> center_ptrs;
  list <Rival *> rival_ptrs;
  list <BattleArena *> arena_ptrs;
  list <GameObject *> :: iterator itr;
  list <Building *> :: iterator bitr;
  list <Pokemon *> :: iterator pitr;
  list <PokemonCenter *> :: iterator citr;
  list <PokemonGym *> :: iterator gitr;
  list <Rival *> :: iterator ritr;
  list <BattleArena *> :: iterator aitr;
public:
  Model();
  ~Model();
  Pokemon * GetPokemonPtr(int id);
  PokemonCenter * GetPokemonCenterPtr(int id);
  PokemonGym * GetPokemonGymPtr(int id);
  Rival * GetRivalPtr(int id);
  BattleArena * GetBattleArenaPtr(int id);
  bool Update();
  void Display(View& view);
  void ShowStatus();
  void NewCommand(char type, int id, Point2D loc);
};

#endif
