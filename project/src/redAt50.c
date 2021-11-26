#include <msp430.h>
#include "stateMachines.h"

//This is just a fragment of the code that can be found in the file for stateMachines.c
//This version of the code redAt50 changes the case statements for if statements
//This is just to show the translation to Assembly

void redAt50();
char state = 0;
if (state == 0)
  {
    red_on = 1;
    state = 1;
  }else (state == 1)
   {
     red_on = 0;
     state = 0;
   }
led_update();
}
