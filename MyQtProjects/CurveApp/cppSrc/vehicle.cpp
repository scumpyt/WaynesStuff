#include "vehicle.h"

Vehicle::Vehicle(const std::string& name,  const std::string& make,
                 const std::string& model, const std::string& year,
                 int curOdom, VehicleTypes::VehicleType vType)

    : myName(name)
    , myMake(make)
    , myModel(model)
    , myYear(year)
    , myOdom(curOdom)
    , myType(vType)
{ }

std::string Vehicle::getName() const
{
    return myName;
}

void Vehicle::setName(const std::string& name)

{
    myName = name;
}

std::string Vehicle::getMake() const
{
    return myMake;
}

void Vehicle::setMake(const std::string& make)

{
    myMake = make;
}

std::string Vehicle::getModel() const
{
    return myModel;
}

void Vehicle::setModel(const std::string& model)

{
    myModel = model;
}

std::string Vehicle::getYear() const
{
    return myYear;
}

void Vehicle::setYear(const std::string& year)

{
    myYear = year;
}

int Vehicle::getOdom() const
{
    return myOdom;
}

void Vehicle::setOdom(int odom)

{
    myOdom = odom;
}

VehicleTypes::VehicleType Vehicle::getVehicleType() const
{
    return myType;
}

void Vehicle::setVehicleType(VehicleTypes::VehicleType vType)

{
    myType = vType;
}

std::string Vehicle::getTypeAsString(VehicleTypes::VehicleType vType)
{
    std::string retStr;
    switch (vType)
    {
    case VehicleTypes::GAS:
        retStr = "GAS";
        break;
    case VehicleTypes::DIESEL:
        retStr = "DIESEL";
        break;
    case VehicleTypes::ELECTRIC:
        retStr = "ELECTRIC";
        break;
    default:
    case VehicleTypes::NoType:
        retStr = "NoType";
        break;
    }

    return retStr;
}

VehicleTypes::VehicleType Vehicle::getTypeFromString(const std::string& strType)
{
    VehicleTypes::VehicleType retType = VehicleTypes::NoType;
    if (strType == "GAS")
    {
        retType = VehicleTypes::GAS;
    }
    else if (strType == "DIESEL")
    {
        retType = VehicleTypes::DIESEL;
    }
    else if (strType == "ELECTRIC")
    {
        retType = VehicleTypes::ELECTRIC;
    }

    return retType;
}

bool Vehicle::isComplete() const
{
    return (!myName.empty()  && !myMake.empty() &&
            !myModel.empty() && !myYear.empty() &&
            myOdom > -1      && myType != VehicleTypes::NoType);
}

bool Vehicle::operator==(const Vehicle& rhs)
{
    if (&rhs == this) return true;      // Check for compare to self...

    // For our purposes here, base a match on name,make,model & year only...
    if (getName() != rhs.getName())
        return false;
    if (getMake() != rhs.getMake())
        return false;
    if (getModel() != rhs.getModel())
        return false;
    if (getYear() != rhs.getYear())
        return false;

    return true;
}

bool Vehicle::operator!=(const Vehicle& rhs)
{
    return !(*this == rhs);
}

// Friend, non-member func...
std::ostream& operator<<(std::ostream& os, const Vehicle& v)
{
    // CSV format...
    os << "VEHICLE,"
       << v.getName() << ","
       << v.getMake() << ","
       << v.getModel() << ","
       << v.getYear() << ","
       << v.getOdom() << ","
       << Vehicle::getTypeAsString(v.getVehicleType()) << ",";

    return os;
}
