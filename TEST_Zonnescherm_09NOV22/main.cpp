#include "test.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::this_thread; //sleep_for, sleep_until
using namespace std::chrono_literals; //ns, us, ms, s, h, etc.
using std::chrono::system_clock;
using namespace std;

int main(void) {

    ResetValuesZonnescherm();

    test1(); //checkparameters should now open zonnescherm

    test2(); //checkparameters should now close zonnescherm

    ResetValuesZonnescherm();

    test3(); //testing initiliazation of hardware components.

    cout << "\n****** End of testing. ******\n";

    return 0;
}
