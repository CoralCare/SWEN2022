#define private public

#include "zonnescherm.h"
#include "buitensensor.h"
#include "binnensensor.h"
#include "uvsensor.h"
#include "states.h"
#include "events.h"
#include "fsm.cpp"
#include "fsm.h"
#include "test.h"

void ResetValuesZonnescherm(){
    cout << "\n***** reseting values zonnescherm *****\n";
    binnensensor.Temp = 18;
    binnensensor.UserTemp = 18;
    buitensensor.Lichtintensiteit = 40;
    buitensensor.Regen =false;
    buitensensor.Windsnelheid = 4;
    uvsensor.UVstraling = 2;
    zonnescherm.OutputParameters();
}

void test1(){
    cout << "\n***** Test1 *****\n";
    cout << "Testing CheckParameters function\n";
    zonnescherm.CheckParameters();
    uvsensor.UVstraling = 6; // > 4
    buitensensor.Lichtintensiteit = 90; // > 80
    cout << "UVstraling set to 6, and Lichtintensiteit set to 90, zonnescherm should now open.\n";
    if(zonnescherm.CheckParameters() == E_OPENING){
        cout << "TEST PASSED: Zonnescherm opens when sun is shining bright. \n";
    }
    else
        {
            cout << "TEST FAILED: Zonnescherm dit not open. \n";
        }
}

void test2(){
    cout << "\n***** Test2 *****\n";
    cout << "Testing CheckParameters function\n";
    zonnescherm.CheckParameters();
    binnensensor.Temp = 16; // < 18
    cout << "Zonnescherm is still open. Binnensensor temp set to 16 degrees, zonnescherm should now close due to low inside temp.\n";
    if(zonnescherm.CheckParameters() == E_CLOSING){
        cout << "TEST PASSED: Zonnescherm closed by lower temperatures . \n";
    }
    else
        {
            cout << "TEST FAILED: Zonnescherm did not close.\n";
        }
}

void test3(){
        cout << "\n***** Test3 *****\n";
        cout << "Testing inititialise function\n";
        zonnescherm.Initialise();
        cout << "\nUVsensor value set to -10, this will result in a init failure.\n";
        uvsensor.UVstraling = -10;
        zonnescherm.OutputParameters();
        if(zonnescherm.Initialise() == E_ERROR){
            cout << "TEST PASSED: inititialise failed.";
        }
        else
            {
                cout << "TEST FAILED: no change in initialization.\n";
            }
}

