///Author: Jasper Verheijen
///482018

#ifndef FSM_H
#define FSM_H

#include "states.h"
#include "events.h"
#include <stdlib.h>


//these function handle the states and events selection
event_e generateEvent(void);
void eventHandler(event_e evnt);

#endif // FSM_H
