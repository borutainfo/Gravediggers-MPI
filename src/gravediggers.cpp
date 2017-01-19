#include <iostream>
#include "distributor/Distributor.h"
#include "process/CityCouncil.h"
#include "process/FuneralHome.h"

using namespace std;

int main(int argc, char **argv) {

    Distributor::initialize();

    /** rada miasta */
    if (Distributor::identityCheck(CITY_COUNCIL)) {
        CityCouncil* cityCouncil = new CityCouncil();
        while(true) {
            cityCouncil->publishDeadList();
            cityCouncil->goDoSomethingElse();
        }
    }

    /** dom pogrzebowy */
    else  {
        FuneralHome *funeralHome = new FuneralHome();
        while(true) {
            funeralHome->getDeathList();
            while(funeralHome->negotiate()) {
                funeralHome->makeFuneral();
                funeralHome->meetWithOfficer();
            }
        }
    }

    Distributor::finalize();

}