#include <iostream>
#include <cstring>
#include "GameObject.h"
#include "Point2D.h"

GameObject :: GameObject(char in_code)
{
  display_code=in_code;
  id_num=1;
  state=0;
  cout << "GameObject constructed" << endl;
}

GameObject :: GameObject(Point2D in_loc, int in_id, char in_code)
{
  location=in_loc;
  id_num=in_id;
  display_code=in_code;
  state=0;
  cout << "GameObject constructed" << endl;
}

GameObject :: ~GameObject()
{
  cout << "GameObject destructed" << endl;
}

bool GameObject :: Update()
{
  //Pure virtual
  return false;
}

bool GameObject :: ShouldBeVisible()
{
  //Pure virtual
  return false;
}

Point2D GameObject :: GetLocation()
{
  //Getter for location
  return location;
}

int GameObject :: GetId()
{
  //Getter for id_num
  return id_num;
}

char GameObject :: GetState()
{
  //Getter for state
  return state;
}

void GameObject :: ShowStatus()
{
  //Simple status call
  cout << display_code << id_num << " located at " << location << endl;
}

void GameObject :: DrawSelf(char* ptr)
{
  //returns identifier to appear on grid
  *ptr=display_code;
  *(ptr+1)=id_num+48; 
  return;
}
