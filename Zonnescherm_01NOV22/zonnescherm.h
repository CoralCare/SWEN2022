///Author: Jasper Verheijen
///482018

#ifndef ZONNESCHERM_H
#define ZONNESCHERM_H
#include "fsm.h"
#include "binnensensor.h"
#include "buitensensor.h"
#include "uvsensor.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::this_thread; //sleep_for, sleep_until
using namespace std::chrono_literals; //ns, us, ms, s, h, etc.
using std::chrono::system_clock;
using namespace std;

class zonnescherm
{
private:
    bool SchakelContactOpen;
    bool SchakelContactDicht;
    int ClosingOpeningTime = 15; //Seconds

public:
    //getter
    bool showSchakelContactOpen() {
        return SchakelContactOpen;
    }

    //getter
    bool showSchakelContactDicht() {
        return SchakelContactDicht;
    }

    //setter
    bool setSchakelContactOpen(bool Semaphore)
    {
        SchakelContactOpen = Semaphore;
        return SchakelContactOpen;
    }

    //setter
    bool setSchakelContactDicht(bool Semaphore)
    {
        SchakelContactDicht = Semaphore;
        return SchakelContactDicht;
    }

    //simuleerd het openen van het zonnescherm.
    void MotorOpen()
    {
        setSchakelContactDicht(false);
        setSchakelContactOpen(false);
        sleep_for (15s);
        setSchakelContactOpen(true);
        cout <<"Zonnescherm wordt geopend, dit duurt " << ClosingOpeningTime << "seconden.\n";
    }

    //simuleerd het openen van het zonnescherm.
    void MotorDicht()
    {
        setSchakelContactDicht(false);
        setSchakelContactOpen(false);
        sleep_for (15s);
        setSchakelContactDicht(true);
        cout <<"Zonnescherm wordt gesloten, dit duurt " << ClosingOpeningTime << "seconden.\n";
    }

    ///Deze functie checked alle inputs op correcte waarde tijdens het initialiseren van het zonnescherm en de sensoren.
    event_e Initialise(void)
    {
       event_e event = E_NO;
          cout << "Initialising all sensors.\n";
          if(uvsensor.InitUVsensor() or binnensensor.InitBinnensensor() or buitensensor.InitBuitensensor() == 1)
          {
            event = E_ERROR;
          }
            else
            {
                event = E_INITIALISED;
            }
       return event;
    }

    ///Checking the different sensors to make sure if the zonnescherm needs to be open or closed.
    void OutputParameters()
    {
       cout << "\nReading all Parameters\n";
       cout << "Binnentemperatuur = " << binnensensor.ShowTemp() << "\n";
       cout << "regen? = " << buitensensor.ShowRegen()  << "\n";
       cout << "Windsnelheid = " << buitensensor.ShowWindsnelheid()  << "\n";
       cout << "lichtintensiteit = " << buitensensor.ShowLichtintensiteit()  << "\n";
       cout << "UV-waarde = " << uvsensor.ShowUV() << "\n";
    }

    ///Deze functie bepaalt de volgende event aan de hand van de huidige parameters.
    event_e CheckParameters(void)
    {
    event_e event = E_NO;

    OutputParameters();

    if (buitensensor.ShowRegen() == true or buitensensor.ShowWindsnelheid() > 12) {
        cout << "Als het regent of te hard waait, moet het zonnescherm dicht!\n";
        event = E_CLOSING;
        return event;
    }

    if (buitensensor.ShowLichtintensiteit() <= 40) {
        cout << "Dicht als het donker is.\n";
        event = E_CLOSING;
        return event;
    }

    if (binnensensor.ShowTemp() < binnensensor.ShowUserTemp() ) {
        cout << "Open als de zon schijnt, maar dicht als de binnentemperatuur lager is dan ingestelde temperatuur gebruiker.\n";
        event = E_CLOSING;
        return event;
    }
        else if (uvsensor.ShowUV() > 4 and buitensensor.ShowLichtintensiteit() >= 80) {
        cout << "Open wanneer de zon schijnt.\n";
        event = E_OPENING;
        }

    return event;
    }

};
zonnescherm zonnescherm;

#endif // ZONNESCHERM_H
