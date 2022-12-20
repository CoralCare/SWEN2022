///Author: Jasper Verheijen
///482018

#ifndef STATES_H
#define STATES_H

typedef enum {
   S_NO, /// Used for initialisation of an state variable.
   S_START,
   S_INITIALISED,
   S_OPEN,
   S_OPENING,
   S_CLOSED,
   S_CLOSING,
   S_ERRORSTATE,
} state_e;

#endif // STATES_H
