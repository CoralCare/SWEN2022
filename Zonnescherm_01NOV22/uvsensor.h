///Author: Jasper Verheijen
///482018

#ifndef UVSENSOR_H
#define UVSENSOR_H
#include <iostream>
using namespace std;

class UVsensor
{
private:
    int UVstraling = 2; //range: 0-15

public:
    //getter
    int ShowUV() {
        return UVstraling;
    }

    //check value of UVstraling if it is in range
    int InitUVsensor()
    {
        int error = 0;

        if(UVstraling > 0 & UVstraling < 15){
            cout << "UVsensor initialised. \n";
        }
            else
            {
                cout << "UVsensor value out of range. \n";
                error = 1;
            }
        return error;
    }
};

UVsensor uvsensor;

#endif // UVSENSOR_H
