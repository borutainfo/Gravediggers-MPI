#include "distributor/Distributor.h"
#include "process/CityCouncil.h"
#include "process/FuneralHome.h"
#include "config.h"

using namespace std;

int main(int argc, char **argv) {
    Distributor::initialize();

    if (Distributor::identityCheck(CITY_COUNCIL)) {
        CityCouncil *cityCouncil = new CityCouncil();
        char a[5];
        a[0] = 'a';
        a[1] = 'b';
        a[2] = 'c';
        a[3] = 'd';
        a[4] = 'e';
        Distributor::send(a, 1);
        Distributor::send(a, 2);
        Distributor::send(a, 3);
    }
    else  {
        char a[5];
        Distributor::receive(&a, 0);
        Debugger::out(a);
        FuneralHome *funeralHome = new FuneralHome();
    }

    Distributor::finalize();
}