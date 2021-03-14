#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point2D.h"

class GameObject
{
protected:
  Point2D location;
  int id_num;
  char display_code;
  char state;

public:
  GameObject(char in_code);
  GameObject(Point2D in_loc, int in_id, char in_code);
  virtual ~GameObject();
  virtual bool Update();
  virtual bool ShouldBeVisible();
  Point2D GetLocation();
  int GetId();
  char GetState();
  virtual void ShowStatus();
  void DrawSelf(char* ptr);
};

#endif
