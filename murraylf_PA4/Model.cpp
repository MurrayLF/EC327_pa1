#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "BattleArena.h"
#include "Rival.h"
#include "View.h"
#include "Model.h"
#include "Input_Handling.h"

using namespace std;

Model :: Model()
{
  //Set time
  tick=0;

  //Create default objects
  pokemon_ptrs.push_back(new Pokemon("Pikachu",5,25,5,8,25,1,'P',Point2D(5,1)));
  pokemon_ptrs.push_back(new Pokemon("Bulbasaur",5,20,10,3,20,2,'P',Point2D(10,1)));
  center_ptrs.push_back(new PokemonCenter(1,1,100,Point2D(1,20)));
  center_ptrs.push_back(new PokemonCenter(2,2,200,Point2D(10,20)));
  gym_ptrs.push_back(new PokemonGym(10,1,2.0,3,1,Point2D(0,0)));
  gym_ptrs.push_back(new PokemonGym(20,5,7.5,8,2,Point2D(5,5)));
  arena_ptrs.push_back(new BattleArena(2,4,3,1,Point2D(20,20)));
  rival_ptrs.push_back(new Rival("James",5,20,6,4,20,1,Point2D(20,20)));
  rival_ptrs.push_back(new Rival("Jesse",5,25,4,5,25,2,Point2D(20,20)));


  pitr=pokemon_ptrs.begin();
  object_ptrs.push_back(*pitr);
  active_ptrs.push_back(*pitr);
  pitr++;
  object_ptrs.push_back(*pitr);
  active_ptrs.push_back(*pitr);
  ritr=rival_ptrs.begin();
  object_ptrs.push_back(*ritr);
  active_ptrs.push_back(*ritr);
  ritr++;
  object_ptrs.push_back(*ritr);
  active_ptrs.push_back(*ritr);
  citr=center_ptrs.begin();
  object_ptrs.push_back(*citr);
  active_ptrs.push_back(*citr);
  citr++;
  object_ptrs.push_back(*citr);
  active_ptrs.push_back(*citr);
  gitr=gym_ptrs.begin();
  object_ptrs.push_back(*gitr);
  active_ptrs.push_back(*gitr);
  gitr++;
  object_ptrs.push_back(*gitr);
  active_ptrs.push_back(*gitr);
  aitr=arena_ptrs.begin();
  object_ptrs.push_back(*aitr);
  active_ptrs.push_back(*aitr);
  (*ritr)->SetArena(*aitr);
  (*(--ritr))->SetArena(*aitr);


  cout << "Model default constructed" << endl;
}

Model :: ~Model()
{
  //Deallocate memory in the heap
  for (itr=object_ptrs.begin();itr!=object_ptrs.end();++itr)
    delete (*itr);
  cout << "Model destructed" << endl;
}

Pokemon * Model :: GetPokemonPtr(int id)
{
  bool check = false;
  int i=0;

  //Determine whether a pokemon with this id_num exists
  pitr=pokemon_ptrs.begin();
  while (!check && pitr!=pokemon_ptrs.end())
  {
    if ((*pitr)->GetId()==id)
      check=true;
    pitr++;
  }
  if (check)
    return *(--pitr);
  else
    return 0;

}

PokemonCenter * Model :: GetPokemonCenterPtr(int id)
{
  bool check = false;
  int i=0;

  //Determine whether a center with this id_num exists
  citr=center_ptrs.begin();
  while (!check && citr!=center_ptrs.end())
  {
    if ((*citr)->GetId()==id)
      check=true;
    citr++;
  }
  if (check)
    return *(--citr);
  else
    return 0;

}

PokemonGym * Model :: GetPokemonGymPtr(int id)
{
  bool check = false;
  int i=0;

  //Determine whether a gym with this id_num exists
  gitr=gym_ptrs.begin();
  while (!check && gitr!=gym_ptrs.end())
  {
    if ((*gitr)->GetId()==id)
      check=true;
    gitr++;
  }
  if (check)
    return *(--gitr);
  else
    return 0;
}

Rival * Model :: GetRivalPtr(int id)
{
  bool check = false;
  int i=0;

  //Determine whether a rival with this id_num exists
  ritr=rival_ptrs.begin();
  while (!check && ritr!=rival_ptrs.end())
  {
    if ((*ritr)->GetId()==id)
      check=true;
    ritr++;
  }
  if (check)
    return *(--ritr);
  else
    return 0;
}

BattleArena * Model :: GetBattleArenaPtr(int id)
{
  bool check = false;
  int i=0;

  //Determine whether an arena with this id_num exists
  aitr=arena_ptrs.begin();
  while (!check && aitr!=arena_ptrs.end())
  {
    if ((*aitr)->GetId()==id)
      check=true;
    aitr++;
  }
  if (check)
    return *(--aitr);
  else
    return 0;
}



bool Model :: Update()
{
  tick++;

  bool check=false,
       ret=false;

  //Update every object
  for (itr=object_ptrs.begin();itr!=object_ptrs.end();++itr)
  {
    check=(*itr)->Update();
    if (check)
      ret=true;
  }

  //Update list of active elements
  for (itr=active_ptrs.begin();itr!=active_ptrs.end();++itr)
  {
    check=(*itr)->ShouldBeVisible();
    if (!check)
      itr=active_ptrs.erase(itr);
  }

  //Whether the game has been beaten
  bool beaten=true;
  for (ritr=rival_ptrs.begin();ritr!=rival_ptrs.end();++ritr)
  {
    if ((*ritr)->IsAlive()==true)
      beaten=false;
  }
  if (beaten)
  {
    cout << "GAME OVER: You win! All rivals beaten!" << endl;
    exit(EXIT_SUCCESS);
  }

  //Whether the game has been lost
  bool lost=true;
  for (pitr=pokemon_ptrs.begin();pitr!=pokemon_ptrs.end();++pitr)
  {
    if ((*pitr)->IsAlive()==true && (*pitr)->IsExhausted()==false)
      lost=false;
  }
  if (lost)
  {
    cout << "GAME OVER: You lose! All of your Pokemon are tired or have fainted!" << endl;
    exit(EXIT_SUCCESS);
  }

  return ret;
}


void Model :: Display(View& view)
{
  //Draw the grid
  for (itr=active_ptrs.begin();itr!=active_ptrs.end();++itr)
    view.Plot(*itr);
  view.Draw();
  return;
}


void Model :: ShowStatus()
{
  //Print the time and status' of all object
  cout << "Time : " << tick << endl;
   for (itr=active_ptrs.begin();itr!=active_ptrs.end();++itr)
  {
    (*itr)->ShowStatus();
  }
}

void Model :: NewCommand(char type, int id, Point2D loc)
{
  try{
    if(type=='p')
    {
      Pokemon * pnt = GetPokemonPtr(id);
      if (pnt!=0)
      {
        Invalid_Input x=Invalid_Input("Invalid ID");
        throw x;
      }

      srand(time(NULL));
      int p=rand()%1000;

      if(p==0)
        pokemon_ptrs.push_back(new Pokemon("Mewtwo",10,1000,100,100,99,id,'P',loc));
      else
        pokemon_ptrs.push_back(new Pokemon("Magikarp",2,5,2,2,5,id,'P',loc));
      //pitr=pokemon_ptrs.back();
      object_ptrs.push_back(pokemon_ptrs.back());
      active_ptrs.push_back(pokemon_ptrs.back());
    }
    else if(type=='c')
    {
      PokemonCenter * pnt = GetPokemonCenterPtr(id);
      if (pnt!=0)
      {
        Invalid_Input x=Invalid_Input("Invalid ID");
        throw x;
      }
      center_ptrs.push_back(new PokemonCenter(id,1,25,loc));
      //citr=center_ptrs.back();
      object_ptrs.push_back(center_ptrs.back());
      active_ptrs.push_back(center_ptrs.back());
    }
    else if(type=='g')
    {
      PokemonGym * pnt = GetPokemonGymPtr(id);
      if (pnt!=0)
      {
        Invalid_Input x=Invalid_Input("Invalid ID");
        throw x;
      }
      gym_ptrs.push_back(new PokemonGym(20,5,7.5,8,id,loc));
      //gitr=gym_ptrs.back();
      object_ptrs.push_back(gym_ptrs.back());
      active_ptrs.push_back(gym_ptrs.back());
    }
    else if(type=='r')
    {
      try{
        Rival * pnt = GetRivalPtr(id);
        if (pnt!=0)
        {
          Invalid_Input x=Invalid_Input("Invalid ID");
          throw x;
        }
        srand(time(NULL));
        int pick=rand()%500;
        if(pick==0)
          rival_ptrs.push_back(new Rival("The Boss",5,20,6,4,20,id,loc));
        else
          rival_ptrs.push_back(new Rival("Meowth",5,20,6,4,20,id,loc));

        //Check to see which arena the rival is in
        aitr=arena_ptrs.begin();
        bool found=false;
        while(!found && aitr!=arena_ptrs.end())
        {
          if((*aitr)->GetLocation().x==loc.x && (*aitr)->GetLocation().y==loc.y)
            found=true;
          else
            aitr++;
        }
        //If there is no arena at this location
        if (!found)
        {
          Invalid_Input x=Invalid_Input("Invalid location; rivals must be in an arena");
          throw x;
        }
        //If there is an arena
        (rival_ptrs.back())->SetArena(*aitr);
        (*aitr)->AddOneRival();
        object_ptrs.push_back(rival_ptrs.back());
        active_ptrs.push_back(rival_ptrs.back());
      }
      catch(Invalid_Input& except){
        cout << "Invalid input - " << except.msg_ptr << endl;
      }
    }
    else
    {
      Invalid_Input x=Invalid_Input("Invalid type");
      throw x;
    }
  }
  catch(Invalid_Input& except){
    cout << "Invalid input - " << except.msg_ptr << endl;
  }
}
