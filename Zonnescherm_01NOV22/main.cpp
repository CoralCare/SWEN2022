// Zonnescherm software - V1) --------------------------------------------

#include "fsm.h"

/// Executes the state machine (FSM: Finite State Machine)
/// an endless loop processing the generated event by a subsystem.
int main(void)
{
   event_e currentEvent = E_START;

   eventHandler(currentEvent);
   // Endless loop
   while (1)
   {
      currentEvent = generateEvent();
      eventHandler(currentEvent);
   }

   return 0;
}
