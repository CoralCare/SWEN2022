///Author: Jasper Verheijen
///482018

#ifndef BUITENSENSOR_H
#define BUITENSENSOR_H
#include <iostream>
using namespace std;

class BuitenSensor
{
private:
    int Lichtintensiteit = 40; //range: 0-130
    bool Regen = false;
    int Windsnelheid = 4; //range: 0-30

public:
    //getter
    int ShowLichtintensiteit() {
        return Lichtintensiteit;
    }
    //getter
    bool ShowRegen() {
        return Regen;
    }
    //getter
    int ShowWindsnelheid() {
        return Windsnelheid;
    }
    //check value of lichtintensiteit & Windsnelheid if it is in range
    int InitBuitensensor()
    {
        int error = 0;

        if(Lichtintensiteit >= 1 & Lichtintensiteit <= 130 & Windsnelheid >= 1 & Windsnelheid <= 30)
        {
            cout << "Buitensensor initialised. \n";
        }
            else {
                cout << "Buitensensor value out of range. \n";
                error = 1;
        }
        return error;
    }
};

BuitenSensor buitensensor;

#endif // BUITENSENSOR_H
