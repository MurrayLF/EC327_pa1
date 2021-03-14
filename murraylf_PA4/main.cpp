#include <iostream>
#include "Point2D.h"
#include "Model.h"
#include "GameCommand.h"
#include "View.h"
#include "Input_Handling.h"

using namespace std;

int main()
{
  Model model;
  View view;
  bool playing=true;
  char code,
       type;
  int ID,
      ID1,
      ID2,
      x,
      y,
      amount;

  //Print initial information
  model.ShowStatus();
  view.Clear();
  model.Display(view);

  while (playing)
  {
    //Get input
    cout << "Enter command: ";
    cin >> code;

    try
    {
      //Perform command
      switch (code){
         case 'm':
          cin >> ID;
          cin >> x;
          cin >> y;
          DoMoveCommand(model,ID,Point2D(x,y));
          break;
         case 'c':
          cin >> ID1;
          cin >> ID2;
          DoMoveToCenterCommand(model,ID1,ID2);
          break;
         case 'g':
          cin >> ID1;
          cin >> ID2;
          DoMoveToGymCommand(model,ID1,ID2);
          break;
         case 'a':
  	      cin >> ID1;
	        cin >> ID2;
 	        DoMoveToArenaCommand(model,ID1,ID2);
 	        break;
         case 's':
          cin >> ID;
          DoStopCommand(model,ID);
          break;
         case 'r':
          cin >> ID;
          cin >> amount;
          DoRecoverInCenterCommand(model,ID,amount);
          break;
         case 't':
          cin >> ID;
          cin >> amount;
          DoTrainInGymCommand(model,ID,amount);
          break;
         case 'b':
	        cin >> ID1;
	        cin >> ID2;
	        DoBattleCommand(model,ID1,ID2);
	        break;
         case 'v':
          DoGoCommand(model,view);
          break;
        case 'x':
          DoRunCommand(model,view);
          break;
        case 'n':
          cin >> type;
          cin >> ID;
          cin >> x;
          cin >> y;
          model.NewCommand(type,ID,Point2D(x,y));
          break;
        case 'q':
          cout << "Terminating Program" << endl;
          playing=false;
          break;
        default:
          Invalid_Input exception = Invalid_Input("Invalid code");
          throw exception;
          break;
      }
    }
    //Action to be taken if input wrong
    catch(Invalid_Input& except){
      cout << "Invalid input - " << except.msg_ptr << endl;
    }

    //Print resulting information
    view.Clear();
    model.Display(view);
  }
}
