#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Pokemon.h"
#include "Building.h"
#include "PokemonGym.h"
#include "PokemonCenter.h"
#include "Model.h"
#include "GameCommand.h"
#include "View.h"
#include "Input_Handling.h"

using namespace std;

void DoMoveCommand(Model & model, int pokemon_id, Point2D p1)
{
  //If pokemon with this ID exists, call start moving
  try{
   Pokemon * poke_ptr=model.GetPokemonPtr(pokemon_id);

   if (poke_ptr==0)
   {
     Invalid_Input x = Invalid_Input("Error: Please enter a valid command!");
     throw x;
   }

   cout << "Moving " << poke_ptr->GetName() << " to " << p1 << endl;
   poke_ptr->StartMoving(p1);
   }

   catch (Invalid_Input& except){
     cout << "Invalid input - " << except.msg_ptr << endl;
   }
}

void DoMoveToCenterCommand(Model & model, int pokemon_id, int center_id)
{
  //If pokemon with this ID exists, call start moving to center
  try{
    Pokemon * poke_ptr=model.GetPokemonPtr(pokemon_id);
    PokemonCenter * cntr_ptr=model.GetPokemonCenterPtr(center_id);

    if (poke_ptr==0 || cntr_ptr==0)
    {
      Invalid_Input x = Invalid_Input("Error: Please enter a valid command!");
      throw x;
    }

    cout << "Moving " << poke_ptr->GetName() << " to center " << cntr_ptr->GetId() << endl;
    poke_ptr->StartMovingToCenter(cntr_ptr);
  }

  catch (Invalid_Input& except){
    cout << "Invalid input - " << except.msg_ptr << endl;
  }
}

void DoMoveToGymCommand(Model & model, int pokemon_id, int gym_id)
{
  //If pokemon with this ID exists, call start moving to gym
  try{
    Pokemon * poke_ptr=model.GetPokemonPtr(pokemon_id);
    PokemonGym * gym_ptr=model.GetPokemonGymPtr(gym_id);

    if (poke_ptr==0 || gym_ptr==0)
    {
      Invalid_Input x = Invalid_Input("Error: Please enter a valid command!");
      throw x;
    }

    cout << "Moving " << poke_ptr->GetName() << " to gym " << gym_ptr->GetId() << endl;
    poke_ptr->StartMovingToGym(gym_ptr);
  }

  catch (Invalid_Input& except){
    cout << "Invalid input - " << except.msg_ptr << endl;
  }
}

void DoMoveToArenaCommand(Model & model, int pokemon_id, int arena_id)
{
  //If pokemon with this ID exists, call start moving to arena
  try{
   Pokemon * poke_ptr=model.GetPokemonPtr(pokemon_id);
   BattleArena * arena_ptr=model.GetBattleArenaPtr(arena_id);

   if (poke_ptr==0 || arena_ptr==0)
   {
     Invalid_Input x = Invalid_Input("Error: Please enter a valid command!");
     throw x;
   }

   cout << "Moving " << poke_ptr->GetName() << " to arena " << arena_ptr->GetId() << endl;
   poke_ptr->StartMovingToArena(arena_ptr);
  }

  catch (Invalid_Input& except){
    cout << "Invalid input - " << except.msg_ptr << endl;
  }
}

void DoStopCommand(Model & model, int pokemon_id)
{
  //If pokemon with this ID exists, call stop
  try{
    Pokemon * poke_ptr=model.GetPokemonPtr(pokemon_id);
    if (poke_ptr==0)
    {
      Invalid_Input x = Invalid_Input("Error: Please enter a valid command!");
      throw x;
    }

    cout << "Stopping " << poke_ptr->GetName() << endl;
    poke_ptr->Stop();
  }

  catch (Invalid_Input& except){
    cout << "Invalid input - " << except.msg_ptr << endl;
  }
}

void DoTrainInGymCommand(Model & model, int pokemon_id, unsigned int training_units)
{
  //If pokemon with this ID exists, call start training
  try{
    Pokemon * poke_ptr=model.GetPokemonPtr(pokemon_id);
    if (poke_ptr==0)
    {
      Invalid_Input x = Invalid_Input("Error: Please enter a valid command!");
      throw x;
    }

    cout << "Training " << poke_ptr->GetName() << endl;
    poke_ptr->StartTraining(training_units);
  }

  catch (Invalid_Input& except){
    cout << "Invalid input - " << except.msg_ptr << endl;
  }
}

void DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int stamina_points)
{
  //If pokemon with this ID exists, call start recovering stamina
  try{
    Pokemon * poke_ptr=model.GetPokemonPtr(pokemon_id);
    if (poke_ptr==0)
    {
      Invalid_Input x = Invalid_Input("Error: Please enter a valid command!");
      throw x;
    }
    cout << "Recovering " << poke_ptr->GetName() <<"\'s Stamina" << endl;
    poke_ptr->StartRecoveringStamina(stamina_points);
  }

  catch (Invalid_Input& except){
    cout << "Invalid input - " << except.msg_ptr << endl;
  }
}

void DoBattleCommand(Model & model, int pokemon_id, int rival_id)
{
  //If pokemon with this ID exists, enter prepare battle with rival
  try{
    Pokemon * poke_ptr=model.GetPokemonPtr(pokemon_id);
    Rival * rival_ptr=model.GetRivalPtr(rival_id);
    if (poke_ptr==0 || rival_ptr==0)
    {
      Invalid_Input x = Invalid_Input("Error: Please enter a valid command!");
      throw x;
    }
    poke_ptr->ReadyBattle(rival_ptr);
  }

  catch (Invalid_Input& except){
    cout << "Invalid input - " << except.msg_ptr << endl;
  }
}


void DoGoCommand(Model& model, View& view)
{
  //Advance the game by one time increment
  cout << "Advancing one tick." << endl;
  model.Update();
  model.ShowStatus();
}

void DoRunCommand(Model& model, View& view)
{
  //Advance the game by up to five time increments or until update returns true
  bool check=false;
  int count=0;
  cout << "Advancing to next event." << endl;
  while(!check && count < 5)
  {
    check=model.Update();
    count++;
  }
  model.ShowStatus();
}
