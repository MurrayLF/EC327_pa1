#include <iostream>
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"

PokemonCenter :: PokemonCenter()
{
  display_code='C';
  stamina_capacity=100;
  num_stamina_points_remaining=stamina_capacity;
  dollar_cost_per_stamina_point=5;
  state=STAMINA_POINTS_AVAILABLE;
  cout << "PokemonCenter default constructed" << endl;
}

PokemonCenter :: PokemonCenter(int in_Id,double stamina_cost,unsigned int stamina_cap,Point2D in_loc)
{
  id_num=in_Id;
  location=in_loc;
  display_code='C';
  stamina_capacity=stamina_cap;
  num_stamina_points_remaining=stamina_capacity;
  dollar_cost_per_stamina_point=stamina_cost;
  state=STAMINA_POINTS_AVAILABLE;
  cout << "PokemonCenter constructed" << endl;
}

PokemonCenter :: ~PokemonCenter()
{
  cout << "PokemonCenter destructed" << endl;
}

bool PokemonCenter :: HasStaminaPoints()
{
  //true if there is stamina remaining
  if(num_stamina_points_remaining==0)
    return false;
  else
    return true;
}

unsigned int PokemonCenter :: GetNumStaminaPointsRemaining()
{
  //Getter for stamina oint remaining
  return num_stamina_points_remaining;
}

bool PokemonCenter :: CanAffordStaminaPoints(unsigned int stamina_points, double budget)
{
  //True if the pokemon has enough money to buy the given number of points
  if (budget >= stamina_points*dollar_cost_per_stamina_point)
    return true;
  else
    return false;
}

double PokemonCenter :: GetDollarCost(unsigned int stamina_points)
{
  //Returns the cost of a given number of points
  return stamina_points*dollar_cost_per_stamina_point;
}

unsigned int PokemonCenter :: DistributeStamina(unsigned int points_needed)
{
  //returns the proper number of stamina points
  if (num_stamina_points_remaining >= points_needed)
  {
    num_stamina_points_remaining=num_stamina_points_remaining-points_needed;
    return points_needed;
  }
  else
  {
    return num_stamina_points_remaining;
    num_stamina_points_remaining=0;
  }
}

bool PokemonCenter :: Update()
{
  //Updates the state of the center
  if (num_stamina_points_remaining == 0 && state == STAMINA_POINTS_AVAILABLE)
  {
    state=NO_STAMINA_POINTS_AVAILABLE;
    display_code='c';
    cout <<  "PokemonCenter " << id_num << " has run out of stamina points." << endl;
    return true;
  }
  else
    return false;
}

void PokemonCenter :: ShowStatus()
{
  //Prints the status of the center; formatted for indent
  cout << "Pokemon Center Status: ";
  Building :: ShowStatus();
  cout << "       " << "Pokemon dollars per stamina point: " << dollar_cost_per_stamina_point << endl;
  cout << "       " << "has " << num_stamina_points_remaining << " stamina point(s) remaining." << endl;
}
