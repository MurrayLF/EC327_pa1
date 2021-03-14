#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "View.h"

using namespace std;

View :: View()
{
  size=11;
  scale=2.0;
  origin.x=0;
  origin.y=0;
}

bool View :: GetSubscripts(int &out_x, int &out_y, Point2D location)
{
  //determine grid coordinates
  out_x=(location.x-origin.x)/scale;
  out_y=(location.y-origin.y)/scale;

  //Check whether within bounds of displayed grid
  if (out_x >= origin.x && out_y >= origin.y && out_x <= origin.x+size && out_y <= origin.y+size)
    return true;
  else
  {
    cout << "An object is outside the display" << endl;
    return false;
  }
}

void View :: Clear()
{
  //Set grid to dots with spaces in between
  for (int j=0;j<view_maxsize;j++)
    for (int k=0;k<view_maxsize;k++)
    {
      grid[k][j][0]='.';
      grid[k][j][1]=' ';
    }
  return;
}

void View :: Plot(GameObject * ptr)
{
  int x,y;

  //Get location
  bool valid=GetSubscripts(x,y,ptr->GetLocation());

  //Determine whether the location is occupied
  bool occupied=false;
  if (grid[y][x][0]!='.' || grid[y][x][1]!=' ')
    occupied=true;

  //Set text to appear at location
  if (valid && !occupied)
    ptr->DrawSelf(grid[y][x]);
  else if (valid && occupied)
  {
    grid[y][x][0]='*';
    grid[y][x][1]=' ';
  }
}

void View :: Draw()
{
  int count=1;
  for (int j=0;j<size;j++)
  {
    //If the size is odd
    if (size%2==1)
    {
      if (count%2==1)
      {
        if ((size-count)*scale>=10)
          cout << (size-count)*scale;
        else
          cout << (size-count)*scale << " ";
      }
      else
        cout << "  ";
      for (int i=0;i<size;i++)
      {
        cout << grid[size-j-1][i][0] << grid[size-j-1][i][1];
      }
      cout << endl;
      count++;
    }
    //If size is even
    else
    {
      if (count%2==0)
      {
        if ((size-count)*scale>=10)
          cout << (size-count)*scale;
        else
          cout << (size-count)*scale << " ";
      }
      else
        cout << "  ";
      for (int i=0;i<size;i++)
      {
        cout << grid[j][i][0] << grid[j][i][1];
      }
      cout << endl;
      count++;
    }
  }

  //Form bottom scale
  count--;
  cout << "  ";
  for (int i=0;i<=size;i++)
  {
    if (i%2==1)
    {
    cout << (size-count)*scale << "  ";
    if (((size-count)*scale)<10)
      cout << " ";
    count-=2;
    }
  }
  cout << endl;
}
