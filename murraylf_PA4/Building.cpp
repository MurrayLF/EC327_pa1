#include <iostream>
#include "GameObject.h"
#include "Point2D.h"
#include "Building.h"

using namespace std;

Building :: Building():GameObject('B')
{
  pokemon_count=0;
  cout << "Building default constructed" << endl;
}

Building :: Building(char in_code,int in_Id,Point2D in_loc):GameObject(in_loc,in_Id,in_code)
{
  pokemon_count=0;
  cout << "Building constructed" << endl;
}

Building :: ~Building()
{
  cout << "Building destructed" << endl;
}

void Building :: AddOnePokemon()
{
  //Adds one pokemon to a given building
  pokemon_count++;
  return;
}

void Building :: RemoveOnePokemon()
{
  //Removes one pokemon from a given building
  if (pokemon_count != 0)
    pokemon_count--;
  return;
}

void Building :: ShowStatus()
{
  //Displays status; formatted for indent
  cout << display_code << id_num << " located at " << location << endl;
  if (pokemon_count==1)
    cout << "       " << pokemon_count << " pokemon is in this building" << endl;
  else
    cout << "       " << pokemon_count << " pokemon are in this building" << endl;
  return;
}

bool Building :: ShouldBeVisible()
{
  //All buildings should be visible
  return 1;
}
