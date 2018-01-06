#include "apiexplorer.h"

#include <string>
#include <iostream>
#include <memory>

#include "vehicle.h"
#include "oilchangeevent.h"
#include "tirerotationevent.h"
#include "scheduledmaintevent.h"
#include "miscevent.h"
#include "maintenancelog.h"

ApiExplorer::ApiExplorer()
{
}

void ApiExplorer::openExistingAndRead()
{
    std::cout << __FUNCTION__ << " ----------------------- START ---------------------\n";

    std::string fName("openExistingAndRead");
    std::string errMsg;

    {   // Step 1 - create fresh log...
        createAndPopulateLog(fName);
    }

    {
        // Now, open it and read from it...
        MaintenanceLog ml;
        ml.openExistingLog(fName, errMsg);

        std::cout << "NOW HAVE " << ml.getNVehicles() << " VEHICLES...\n";
        ml.listAllVehicles(std::cout);

        std::cout << "NOW HAVE " << ml.getNLogEvents() << " EVENTS...\n";
        ml.listAllEvents(std::cout);

        ml.close();
    }

    // Clean up...
    MaintenanceLog ml;
    ml.deleteLog(fName,errMsg);

    std::cout << __FUNCTION__ << " -----------------------  END  ---------------------\n\n";
}

void ApiExplorer::showVehicleListingOptions()
{
    std::cout << __FUNCTION__ << " ----------------------- START ---------------------\n";

    std::string fName("showVehicleListingOptions");
    std::string errMsg;

    {   // Step 1 - create fresh log...
        createAndPopulateLog(fName);
    }

    {
        // Now, open it and do listing options...
        MaintenanceLog ml;
        ml.openExistingLog(fName, errMsg);

        std::cout << "--- Vehicle listing option 1 - call convenience function to list all:\n";
        ml.listAllVehicles(std::cout);

        std::cout << "--- Vehicle listing option 2 - call getVehicles and do manually:\n";
        const std::vector<Vehicle>& myGarage = ml.getVehicles();
        for(auto v : myGarage)
        {
            std::cout << v << std::endl;
        }

        std::cout << "--- Vehicle listing option 3 - Manually filter for only GAS Vehicles, say:\n";
        for(auto v : myGarage)
        {
            if (v.getVehicleType() == VehicleTypes::GAS)
            {
                std::cout << v << std::endl;
            }
        }
    }

    // Clean up...
    MaintenanceLog ml;
    ml.deleteLog(fName,errMsg);

    std::cout << __FUNCTION__ << " -----------------------  END  ---------------------\n\n";
}

void ApiExplorer::showEventListingOptions()
{
    std::cout << __FUNCTION__ << " ----------------------- START ---------------------\n";

    std::string fName("showEventListingOptions");
    std::string errMsg;

    {   // Step 1 - create fresh log...
        createAndPopulateLog(fName);
    }

    {
        // Now, open it and do listing options...
        MaintenanceLog ml;
        ml.openExistingLog(fName, errMsg);

        std::cout << "--- Event listing option 1 - call convenience function to list all:\n";
        ml.listAllEvents(std::cout);

        std::cout << "--- Event listing option 2 - call getEvents and manually list Events ONLY:\n";
        const std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >& eVect = ml.getEvents();
        for (auto itr=eVect.begin(); itr!=eVect.end(); ++itr)
        {
            std::string derivedClassName = typeid(*itr->first).name();
            if (derivedClassName == "class OilChangeEvent")
            {
                std::cout << dynamic_cast<const OilChangeEvent&>(*(itr->first)) << std::endl;
            }
            else if (derivedClassName == "class TireRotationEvent")
            {
                std::cout << dynamic_cast<const TireRotationEvent&>(*(itr->first)) << std::endl;
            }
            else if (derivedClassName == "class ScheduledMaintEvent")
            {
                std::cout << dynamic_cast<const ScheduledMaintEvent&>(*(itr->first)) << std::endl;
            }
            else if (derivedClassName == "class MiscEvent")
            {
                std::cout << dynamic_cast<const MiscEvent&>(*(itr->first)) << std::endl;
            }
        }

        std::cout << "--- Event listing option 3 - manually filter on Shop=='Kramer Mazda', say:\n";
        //eVect = ml.getEvents();
        for (auto itr=eVect.begin(); itr!=eVect.end(); ++itr)
        {
            if ((*itr->first).getShop() == "Kramer Mazda")
            {
                std::string derivedClassName = typeid(*itr->first).name();
                if (derivedClassName == "class OilChangeEvent")
                {
                    std::cout << dynamic_cast<const OilChangeEvent&>(*(itr->first)) << std::endl;
                }
                else if (derivedClassName == "class TireRotationEvent")
                {
                    std::cout << dynamic_cast<const TireRotationEvent&>(*(itr->first)) << std::endl;
                }
                else if (derivedClassName == "class ScheduledMaintEvent")
                {
                    std::cout << dynamic_cast<const ScheduledMaintEvent&>(*(itr->first)) << std::endl;
                }
                else if (derivedClassName == "class MiscEvent")
                {
                    std::cout << dynamic_cast<const MiscEvent&>(*(itr->first)) << std::endl;
                }
            }
        }
    }

    // Clean up...
    MaintenanceLog ml;
    ml.deleteLog(fName,errMsg);

    std::cout << __FUNCTION__ << " -----------------------  END  ---------------------\n\n";
}

void ApiExplorer::updateExistingRecord()
{
    std::cout << __FUNCTION__ << " ----------------------- START ---------------------\n";

    std::string fName("updateExistingRecord");
    std::string errMsg;

    {   // Step 1 - create fresh log...
        createAndPopulateLog(fName);
    }
    {
        // Now, open it and update an Event...
        MaintenanceLog ml;
        ml.openExistingLog(fName, errMsg);

        std::cout << "--- List all BEFORE update...\n";
        ml.listAllEvents(std::cout);

        size_t idToUpdate = 1;  // Update the first record...
        if (ml.hasEvent(idToUpdate))
        {
            std::unique_ptr<ServiceEventBase> uPtr;
            Vehicle v;

            if (ml.hasEvent(idToUpdate))
            {
                // Get original (copies)...
                ml.getEvent(idToUpdate,uPtr,v,errMsg);

                // Make changes...
                uPtr->setShop("Little Shop Of Horrors!");

                // Update...
                ml.updateEvent(std::move(uPtr), v, errMsg);

                std::cout << "--- List all AFTER update...\n";
                ml.listAllEvents(std::cout);
            }
        }
    }

    // Clean up...
    MaintenanceLog ml;
    ml.deleteLog(fName,errMsg);

    std::cout << __FUNCTION__ << " -----------------------  END  ---------------------\n\n";
}

void ApiExplorer::removeEntries()
{
    std::cout << __FUNCTION__ << " ----------------------- START ---------------------\n";

    std::string fName("removeEntries");
    std::string errMsg;

    {   // Step 1 - create fresh log...
        createAndPopulateLog(fName);
    }
    {
        // Now, open it and do removes...
        MaintenanceLog ml;
        ml.openExistingLog(fName, errMsg);

        std::cout << "--- List all BEFORE removing...\n";
        ml.listAllEvents(std::cout);

        // Remove event 5...
        if (ml.hasEvent(5))
        {
            ml.removeEvent(5, errMsg);

            std::cout << "--- List all AFTER removing Id 5...\n";
            ml.listAllEvents(std::cout);
        }

        // Now remove all Entries for a specific vehicle...
        if (ml.hasVehicle("Wayne's Car"))
        {
            ml.removeAllEvents("Wayne's Car",errMsg);

            std::cout << "--- List all AFTER removing all Events for 'Wayne's Car'...\n";
            ml.listAllEvents(std::cout);
        }
    }

    // Clean up...
    MaintenanceLog ml;
    ml.deleteLog(fName,errMsg);

    std::cout << __FUNCTION__ << " -----------------------  END  ---------------------\n\n";
}

void ApiExplorer::tryToAddOilChangeToElectricCar()
{
    std::cout << __FUNCTION__ << " ----------------------- START ---------------------\n";

    std::string fName("tryToAddOilChangeToElectricCar");
    std::string errMsg;

    {   // Step 1 - create fresh log...
        createAndPopulateLog(fName);
    }

    {
        // Now, open it and read from it...
        MaintenanceLog ml;
        ml.openExistingLog(fName, errMsg);

        // Fetch the electric car...
        Vehicle tesla;
        ml.getVehicle("Wayne's Toy", tesla, errMsg);

        // Create an OilChangeEvent...
        std::unique_ptr<ServiceEventBase> ePtr;
        ePtr.reset(new OilChangeEvent       (22, "04/23/17", "Bonavista Esso", 135123,
                                            "Regular Spring/Autumn stuff.", 75));

        // Now, try to add...
        if (ml.addEvent(std::move(ePtr), tesla, errMsg) == false)
        {
            std::cout << errMsg << "\n";
        }
        else
        {
            std::cout << "Oooops! Adding OilChange to ELECTRIC car worked!!! Fail!\n";
        }

        ml.close();
    }

    // Clean up...
    MaintenanceLog ml;
    ml.deleteLog(fName,errMsg);

    std::cout << __FUNCTION__ << " -----------------------  END  ---------------------\n\n";
}

////////////////////////
// Helper funcs...
void ApiExplorer::createAndPopulateLog(const std::string& fileName)
{
    // Start from scratch...
    MaintenanceLog ml;
    std::string errMsg;

    ml.createNewLog(fileName, errMsg);

    // Add vehicles...
    Vehicle mazda("Wayne's Car","Mazda","CX9","2010",137000,VehicleTypes::GAS);
    Vehicle workTruck("Work Truck", "Ford","F350","2012",45000,VehicleTypes::DIESEL);
    Vehicle van("The Van", "Mazda","MX5","2002",225000,VehicleTypes::GAS);
    Vehicle tesla("Wayne's Toy", "Tesla","Roadster","2017",5000,VehicleTypes::ELECTRIC);

    ml.addVehicle(mazda, errMsg);
    ml.addVehicle(workTruck, errMsg);
    ml.addVehicle(van, errMsg);
    ml.addVehicle(tesla, errMsg);

    // Add events...
    std::unique_ptr<ServiceEventBase> ePtr;

    ePtr.reset(new MiscEvent            (1, "11/16/16", "Kramer Mazda", 134321,
                                        "Replace front wipers.", 20));
    ml.addEvent(std::move(ePtr), mazda, errMsg);

    ePtr.reset(new OilChangeEvent       (2, "04/23/17", "Bonavista Esso", 135123,
                                        "Regular Spring/Autumn stuff.", 75));
    ml.addEvent(std::move(ePtr), workTruck, errMsg);

    ePtr.reset(new TireRotationEvent    (3, "04/23/17", "Bonavista Esso", 135123,
                                        "Regular Spring/Autumn stuff.", 125));
    ml.addEvent(std::move(ePtr), van, errMsg);

    ePtr.reset(new ScheduledMaintEvent  (4, "04/23/17", "Bonavista Esso", 135123,
                                        "Cabin filter replaced.", 170, ScheduledMaintTypes::CABIN_AIR_FILTER,
                                        40000, 24));
    ml.addEvent(std::move(ePtr), mazda, errMsg);

    ePtr.reset(new ScheduledMaintEvent  (5, "04/23/17", "Bonavista Esso", 135123,
                                        "Coolant flushed.", 60, ScheduledMaintTypes::COOLANT_FLUSH,
                                        20000, 18));
    ml.addEvent(std::move(ePtr), tesla, errMsg);

    ePtr.reset(new MiscEvent            (6, "06/15/17", "Kramer Mazda", 136004,
                                        "Ignition Knob replaced.", 5));
    ml.addEvent(std::move(ePtr), mazda, errMsg);

    // Save to output file, & close...
    ml.save(errMsg);
    ml.close();
}
