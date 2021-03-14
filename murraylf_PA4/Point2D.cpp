#include <cmath>
#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"

using namespace std;

Point2D :: Point2D()
{
  x=0.0;
  y=0.0;
}

Point2D :: Point2D(double in_x,double in_y)
{
  x=in_x;
  y=in_y;
}

double GetDistanceBetween(Point2D p1,Point2D p2)
{
  //Returns linear distance between two points
  return (sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2)));
}

ostream& operator << (ostream& out,Point2D p1)
{
  //Displays a Point2D (x,y)
  out << "(" << p1.x << "," << p1.y << ")";
  return out;
}

Point2D operator + (Point2D p1, Vector2D v1)
{
  //Returns the point at the end of the vector which the tail is on p1
  Point2D pout;
  pout.x=p1.x+v1.x;
  pout.y=p1.y+v1.y;
  return pout;
}

Vector2D operator - (Point2D p1,Point2D p2)
{
  //Return the vector expressing the x and y distance between the two points
  Vector2D vout;
  vout.x=p1.x-p2.x;
  vout.y=p1.y-p2.y;
  return vout;
}
