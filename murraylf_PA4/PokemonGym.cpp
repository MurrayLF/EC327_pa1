#include "GameObject.h"
#include "Building.h"
#include "PokemonGym.h"
#include <iostream>

using namespace std;

PokemonGym :: PokemonGym()
{
  display_code='G';
  state=NOT_BEATEN;
  max_number_of_training_units=10;
  num_training_units_remaining=max_number_of_training_units;
  stamina_cost_per_training_unit=1;
  dollar_cost_per_training_unit=1.0;
  experience_points_per_training_unit=2;
  cout << "PokemonGym default constructed" << endl;
}

PokemonGym :: PokemonGym(unsigned int max_training_units, unsigned int stamina_cost, double
dollar_cost, unsigned int exp_points_per_unit, int in_id, Point2D in_loc)
{
  display_code='G';
  state=NOT_BEATEN;
  id_num=in_id;
  max_number_of_training_units=max_training_units;
  num_training_units_remaining=max_number_of_training_units;
  stamina_cost_per_training_unit=stamina_cost;
  experience_points_per_training_unit=exp_points_per_unit;
  dollar_cost_per_training_unit=dollar_cost;
  location=in_loc;
  cout << "PokemonGym constructed" << endl;
}

PokemonGym :: ~PokemonGym()
{
  cout << "PokemonGym destructed" << endl;
}

double PokemonGym :: GetDollarCost(unsigned int unit_qty)
{
  //Returns the dollar cost of a given quantity of units
  return unit_qty*dollar_cost_per_training_unit;
}

unsigned int PokemonGym :: GetStaminaCost(unsigned int unit_qty)
{
  //Returns the stamina cost of a given quantity of units
  return unit_qty*stamina_cost_per_training_unit;
}

unsigned int PokemonGym :: GetNumTrainingUnitsRemaining()
{
  //Getter for the number of units in a gym
  return num_training_units_remaining;
}

bool PokemonGym :: IsAbleToTrain(unsigned int unit_qty, double budget, unsigned int stamina)
{
  //Determines whether a pokemon with a given budget and stamina can train for a given quantity of units
  if (unit_qty*dollar_cost_per_training_unit <= budget && unit_qty*stamina_cost_per_training_unit <= stamina)
    return true;
  else
    return false;
}

unsigned int PokemonGym :: TrainPokemon(unsigned int training_units)
{
  //Returns the number of training units possible
  if (training_units <= num_training_units_remaining)
  {
    num_training_units_remaining=num_training_units_remaining-training_units;
    return training_units*experience_points_per_training_unit;
  }
  else
  {
    return num_training_units_remaining*experience_points_per_training_unit;
    num_training_units_remaining=0;
  }
}

bool PokemonGym :: Update()
{
  //Updates the gym's state
  if(num_training_units_remaining==0 && state != BEATEN)
  {
    state=BEATEN;
    display_code='g';
    cout << display_code  << id_num << " has been beaten" << endl;
    return true;
  }
  else
    return false;
}

bool PokemonGym :: IsBeaten()
{
  //Returns whether the gym has been beaten or not
  if (num_training_units_remaining==0)
    return true;
  else
    return false;
}

void PokemonGym :: ShowStatus()
{
  //Returns the status of the gym; formatted for indent
  cout << "Pokemon Gym status: ";
  Building :: ShowStatus();
  cout << "       Max number of training units: " << max_number_of_training_units << endl;
  cout << "       Stamina cost per training unit: " << stamina_cost_per_training_unit << endl;
  cout << "       Pokemon dollar per training unit: " << dollar_cost_per_training_unit << endl;
  cout << "       Experience points per training unit: " << experience_points_per_training_unit << endl;
  cout << "       " << num_training_units_remaining << " training unit(s) are remaining for this gym" << endl;
  return;
}
