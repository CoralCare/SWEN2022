///Author: Jasper Verheijen
///482018

#ifndef BINNENSENSOR_H
#define BINNENSENSOR_H
#include <iostream>
using namespace std;

class BinnenSensor
{
private:

    int Temp = 18; // degrees celsius
    int UserTemp = 18; // degrees celsius

public:
    //getter
    int ShowTemp() {
        return Temp;
    }

    int ShowUserTemp() {
        return UserTemp;
    }

    //setter for usertemp adjustment
    int AdjustUserTemp(int NewUserTemp) {
        UserTemp = NewUserTemp;
        return UserTemp;
    }
    //check value of UVstraling if it is in range
    int InitBinnensensor()
    {
        int error = 0;

        if(Temp >= 0 & Temp <= 30 & UserTemp >= 10 & UserTemp <= 30){
            cout << "Binnensensor initialised. \n";
        }
        else {
            cout << "Binnensensor value out of range. \n";
            error = 1;
        }
        return error;
    }
};

BinnenSensor binnensensor;

#endif // BINNENSENSOR_H

