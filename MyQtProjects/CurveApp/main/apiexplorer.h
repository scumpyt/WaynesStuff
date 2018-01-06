#ifndef APIEXPLORER_H
#define APIEXPLORER_H

#include <string>

class ApiExplorer
{
public:
    ApiExplorer();

    /// ----------------------------------------------------------------------
    /// API demonstration app of the requested basics.
    ///
    /// In your "Programming Problem" the requirements stated:
    ///  - "Your library or API should be capable of listing, adding,
    ///    updating and removing entries at runtime."
    ///  - "Not all maintenance tasks can be applied to all vehicles
    ///    (an electric car won’t need an oil change)"
    ///  - "Demonstrate usage using an interface."
    ///
    /// This app will attempt to do the above. - The full API is
    /// tested in the Unit Tests.
    /// ----------------------------------------------------------------------

    static void openExistingAndRead();
    static void showVehicleListingOptions();
    static void showEventListingOptions();
    static void updateExistingRecord();
    static void removeEntries();
    static void tryToAddOilChangeToElectricCar();

protected:
    /// Demonstrates adding both Vehicles and Events...
    static void createAndPopulateLog(const std::string& fileName);
};

#endif // APIEXPLORER_H
