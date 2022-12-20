///Author: Jasper Verheijen
///482018

#include <chrono>
#include <thread>
#include <iostream>

using namespace std::this_thread; //sleep_for, sleep_until
using namespace std::chrono_literals; //ns, us, ms, s, h, etc.
using std::chrono::system_clock;
using namespace std;

#include "binnensensor.h"
#include "buitensensor.h"
#include "fsm.h"
#include "uvsensor.h"
#include "zonnescherm.h"
#include "states.h"
#include "events.h"

state_e currentState = S_NO;
event_e event = E_NO;

/// Because we do not buffer events in an event queue, we send in the
/// current state, #currentState, only events that can be handled.
/// @return Generated event for the #eventHandler function.
event_e generateEvent(void)
{
   event_e evnt = E_NO;
   switch(currentState)
   {
      case S_NO:
         cout <<"DEBUG: Current state is not initialised.\n";
         break;
      case S_START:
         cout << "DEBUG: Zonnescherm software is starting up. components getting initialised.\n";
         evnt = zonnescherm.Initialise();
         break;
      case S_INITIALISED:
         cout <<"DEBUG: Software is initialised.\n";
         break;
      case S_CLOSED:
         cout <<"DEBUG: Software is in CLOSED state.\n";
         evnt = zonnescherm.CheckParameters();
         break;
      case S_OPENING:
         cout <<"DEBUG: Software is in OPENING state.\n";
         break;
      case S_OPEN:
         cout <<"DEBUG: Software is in OPEN state.\n";
         evnt = zonnescherm.CheckParameters();
         break;
      case S_CLOSING:
         cout <<"DEBUG: Software is in CLOSING state.\n";
         break;
      case S_ERRORSTATE:
         cout <<"DEBUG: Software is in ERROR state.\n";
         evnt = E_ERROR;
         break;
   }
   return evnt;
}

/// Uses the global variable #currentState to determine how to process the
/// received #event.
/// If an #event is received that should not be in handled in the
/// currentState this is considered as a system error.
/// The switch statements use the default case to show an appropriate message
/// to the display.
/// It is necessary to give in all default cases the nextState an appropriate
/// value to avoid undefined behaviour.
/// @post Updated #currentState by nextState.
void eventHandler(event_e event)
{
   state_e nextState = S_NO;

   switch(currentState)
   {
      case S_START:
         switch(event) {
         case E_ERROR:
             nextState = S_ERRORSTATE;
             break;
         case E_INITIALISED:
             nextState = S_INITIALISED;
             break;
         default:
             cout << "software in unknown state... will restart...\n";
             nextState = S_START;
         }
         break;

      case S_INITIALISED:
          nextState = S_CLOSED;
          break;

      case S_CLOSED:
          switch(event) {
          case E_OPENING:
              cout << "zonnescherm will open.\n";
              nextState = S_OPENING;
              break;
          default:
              cout << "zonnescherm is already closed.\n";
              sleep_for (15s);
              nextState = S_CLOSED;
          }
          break;

      case S_OPENING:
         if (zonnescherm.showSchakelContactDicht()== true)
         {
           zonnescherm.MotorOpen();
            if(zonnescherm.showSchakelContactOpen()== true) //pas naar volgende state als het zonnescherm open is.
            {
                nextState = S_OPEN;
            }
         }
            else
            {
                cout << "DEBUG: Zonnescherm is already open.\n";
                nextState = S_ERRORSTATE;
            }
         break;

      case S_OPEN:
         switch(event) {
         case E_CLOSING:
            cout << "zonnescherm will now close.\n";
            nextState = S_CLOSING;
            break;
         default:
            cout << "zonnescherm is already open.\n";
            sleep_for (15s);
            nextState = S_OPEN;
        }
        break;

      case S_CLOSING:
        if (zonnescherm.showSchakelContactOpen()== true)
        {
             zonnescherm.MotorDicht();
             if(zonnescherm.showSchakelContactDicht()== true) //pas naar volgende state als het zonnescherm dicht is.
             {
                 nextState = S_CLOSED;
             }
        }
             else
             {
                 cout << "DEBUG: Zonnescherm is already closed.\n";
                 nextState = S_ERRORSTATE;
             }
        break;

      case S_ERRORSTATE:
         nextState = S_START;
         break;

      default:
         cout <<"Software is in UNKNOWN current state\n";
         cout <<"Software will re-start...\n";
         nextState = S_START;
         break;
   }
   currentState = nextState;
}
