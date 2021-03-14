#include <ostream>
#include "Vector2D.h"

using namespace std;


Vector2D :: Vector2D()
{
  x=0.0;
  y=0.0;
}

Vector2D :: Vector2D(double in_x,double in_y)
{
  x=in_x;
  y=in_y;
}

Vector2D operator * (Vector2D v1,double d)
{
  //Multiplies vector by double
  Vector2D vout;
  vout.x=v1.x*d;
  vout.y=v1.y*d;
  return vout;
}

Vector2D operator / (Vector2D v1,double d)
{
  //Return v1 when divider is 0
  if (d==0)
    return v1;
  //Divide v1 by d when not
  else
  {
    Vector2D vout;
    vout.x=v1.x/d;
    vout.y=v1.y/d;
    return vout;
  }
 }

ostream& operator << (ostream& out,Vector2D v1)
{
  //Displays a Vecotr2D as <x,y>
  out << "<" << v1.x << "," << v1.y << ">";
  return out;
}
