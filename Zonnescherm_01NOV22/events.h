///Author: Jasper Verheijen
///482018

#ifndef EVENTS_H
#define EVENTS_H

typedef enum {
   E_NO,  /// Used for initialisation of an event variable.
   E_INITIALISED,
   E_ERROR,
   E_START,
   E_SOLVED,
   E_STANDBY,
   E_CLOSED,
   E_OPENING,
   E_OPEN,
   E_CLOSING,
} event_e;

#endif // EVENTS_H
