#include "persistenceengine.h"
#include "oilchangeevent.h"
#include "miscevent.h"
#include "scheduledmaintevent.h"
#include "tirerotationevent.h"
#include <sstream>

#include <QString>
#include <QStringList>

PersistenceEngine::PersistenceEngine()
{

}

std::string PersistenceEngine::getLogFileName() const
{
    return myLogFileName;
}

void PersistenceEngine::setLogFileName(const std::string& logFileName)
{
    myLogFileName = logFileName;
}

bool PersistenceEngine::checkForOpen(const std::string& funcName, std::string& errMsg) const
{
    errMsg.clear();
    if (!isOpen())
    {
        errMsg = funcName + ": No file open yet.";
        return false;
    }
    return true;
}

std::string  PersistenceEngine::formatEventOutput(const ServiceEventBase* e, const Vehicle& v)
{
    std::stringstream ss;

    std::string derivedClassName = typeid(*e).name();
    if (derivedClassName == "class OilChangeEvent")
    {
        ss << dynamic_cast<const OilChangeEvent&>(*e) << " --- on --- ," << v << std::endl;
    }
    else if (derivedClassName == "class TireRotationEvent")
    {
        ss << dynamic_cast<const TireRotationEvent&>(*e) << " --- on --- ," << v << std::endl;
    }
    else if (derivedClassName == "class ScheduledMaintEvent")
    {
        ss << dynamic_cast<const ScheduledMaintEvent&>(*(e)) << " --- on --- ," << v << std::endl;
    }
    else if (derivedClassName == "class MiscEvent")
    {
        ss << dynamic_cast<const MiscEvent&>(*e) << " --- on --- ," << v << std::endl;
    }

    return ss.str();
}

bool PersistenceEngine::parseLineForVehicle(const std::string& inLine, Vehicle& outVehicle)
{
    // Totally cheated and used Qt to do this is as it's so easy.
    // Could easily be refactored to remove Qt.
    QStringList tokens = QString::fromStdString(inLine).split(',');

    if (tokens.at(0) == "VEHICLE" && tokens.size() >= 7)
    {
        // Convert type from string...
        VehicleTypes::VehicleType vType = Vehicle::getTypeFromString(tokens.at(6).toStdString());

        outVehicle = Vehicle(tokens.at(1).toStdString(),        // name
                             tokens.at(2).toStdString(),        // make
                             tokens.at(3).toStdString(),        // model
                             tokens.at(4).toStdString(),        // year
                             tokens.at(5).toInt(),              // odom
                             vType                              // type
                             );
        return true;
    }
    else
    {
        outVehicle = Vehicle();
        return false;
    }
}

bool PersistenceEngine::parseLineForEvent(const std::string& inLine,
                                          std::pair< std::unique_ptr<ServiceEventBase>, Vehicle >& e)
{
    // Totally cheated and used Qt to do this is as it's so easy.
    // Could easily be refactored to remove Qt.
    QStringList tokens = QString::fromStdString(inLine).split(',');

    if (tokens.at(0) == "EVENT" && tokens.size() >= 16)
    {
        // 16 tokens is the min for MiscEvent - check for greater in others!!!

        // Pull out the base class bits first... They are common for all...
        size_t id           = tokens.at(1).toInt();
        std::string name    = tokens.at(2).toStdString();
        std::string date    = tokens.at(3).toStdString();
        std::string shop    = tokens.at(4).toStdString();
        int odom            = tokens.at(5).toInt();
        std::string notes   = tokens.at(6).toStdString();
        float cost          = tokens.at(7).toFloat();

        // Do events first... Type based on Event name...
        if (tokens.at(2) == "Oil Change" && tokens.size() >= 18)
        {
            e.first.reset(new OilChangeEvent(id,date,shop,odom,notes,cost,
                              tokens.at(8).toInt(),             // repeatOdom
                              tokens.at(9).toInt()              // repeatMonths
                              ));

            VehicleTypes::VehicleType vType = Vehicle::getTypeFromString(tokens.at(17).toStdString());
            e.second = Vehicle(tokens.at(12).toStdString(),     // name
                               tokens.at(13).toStdString(),     // make
                               tokens.at(14).toStdString(),     // model
                               tokens.at(15).toStdString(),     // year
                               tokens.at(16).toInt(),           // odom
                               vType                            // type
                               );
            return true;
        }
        else if (tokens.at(2) == "Tire Rotation" && tokens.size() >= 18)
        {
            e.first.reset(new TireRotationEvent(id,date,shop,odom,notes,cost,
                              tokens.at(8).toInt(),             // repeatOdom
                              tokens.at(9).toInt()              // repeatMonths
                              ));

            VehicleTypes::VehicleType vType = Vehicle::getTypeFromString(tokens.at(17).toStdString());
            e.second = Vehicle(tokens.at(12).toStdString(),     // name
                               tokens.at(13).toStdString(),     // make
                               tokens.at(14).toStdString(),     // model
                               tokens.at(15).toStdString(),     // year
                               tokens.at(16).toInt(),           // odom
                               vType                            // type
                               );
            return true;
        }
        else if (tokens.at(2) == "Scheduled Event" && tokens.size() >= 19)
        {
            ScheduledMaintTypes::ScheduledMaintType mType = ScheduledMaintEvent::getMaintTypeFromString(tokens.at(10).toStdString());
            e.first.reset(new ScheduledMaintEvent(id,date,shop,odom,notes,cost,
                              mType,                            // maintType
                              tokens.at(8).toInt(),             // repeatOdom
                              tokens.at(9).toInt()              // repeatMonths
                              ));

            VehicleTypes::VehicleType vType = Vehicle::getTypeFromString(tokens.at(18).toStdString());
            e.second = Vehicle(tokens.at(13).toStdString(),     // name
                               tokens.at(14).toStdString(),     // make
                               tokens.at(15).toStdString(),     // model
                               tokens.at(16).toStdString(),     // year
                               tokens.at(17).toInt(),           // odom
                               vType                            // type
                               );
            return true;
        }
        else if (tokens.at(2) == "Misc Event")
        {
            e.first.reset(new MiscEvent(id,date,shop,odom,notes,cost));

            VehicleTypes::VehicleType vType = Vehicle::getTypeFromString(tokens.at(15).toStdString());
            e.second = Vehicle(tokens.at(10).toStdString(),     // name
                               tokens.at(11).toStdString(),     // make
                               tokens.at(12).toStdString(),     // model
                               tokens.at(13).toStdString(),     // year
                               tokens.at(14).toInt(),           // odom
                               vType                            // type
                               );
            return true;
        }
        else
        {
            e.first.reset(nullptr);
            e.second = Vehicle();
            return false;
        }
    }
    else
    {
        e.first.reset(nullptr);
        e.second = Vehicle();
        return false;
    }
}
