#include <iostream>

#include "vehicle.h"
#include "apiexplorer.h"

int main()
{
    try
    {
        {
            ApiExplorer ex;
            ex.openExistingAndRead();
        }
        {
            ApiExplorer ex;
            ex.showVehicleListingOptions();
        }
        {
            ApiExplorer ex;
            ex.showEventListingOptions();
        }
        {
            ApiExplorer ex;
            ex.updateExistingRecord();
        }
        {
            ApiExplorer ex;
            ex.removeEntries();
        }
        {
            ApiExplorer ex;
            ex.tryToAddOilChangeToElectricCar();
        }
    }
    catch (...)
    {
        std::cout << "An exception was caught in main... Program terminating..." << std::endl;
        return -1;
    }

    return 0;
}
