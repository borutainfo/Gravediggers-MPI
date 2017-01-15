#include "distributor/Distributor.h"
#include "process/CityCouncil.h"
#include "process/FuneralHome.h"
#include "config.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
using namespace std;

int main(int argc, char **argv) {
    Distributor::initialize();

    if (Distributor::identityCheck(CITY_COUNCIL)) {
        CityCouncil* cityCouncil = new CityCouncil();
//        while(true) {
            cityCouncil->publishDeadList();
            cityCouncil->goDoSomethingElse();
//        }
    }
    else  {
        FuneralHome *funeralHome = new FuneralHome();
//        while(true) {
            funeralHome->getDeathList();
            funeralHome->selectCorpse();
//        }
    }
    Distributor::finalize();
}
#pragma clang diagnostic pop