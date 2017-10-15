#include "scheduledmaintevent.h"

ScheduledMaintEvent::ScheduledMaintEvent(size_t id,
                                         const std::string& date, const std::string& shop,
                                         int curOdom,
                                         const std::string& notes, float preTaxCost,
                                         ScheduledMaintTypes::ScheduledMaintType mType,
                                         int repeatOdom, int repeatMonths)
    : ServiceEventBase(id, date, shop, curOdom, notes, preTaxCost)
    , myMaintType(mType)
    , myRepeatOdom(repeatOdom)
    , myRepeatMonths(repeatMonths)
{

}


std::string ScheduledMaintEvent::getName() const
{
    return "Scheduled Event";
}

std::string ScheduledMaintEvent::getReminderString() const
{
    std::string retStr = "Repeat in: " +
                         std::to_string(myRepeatOdom)   + " kms or " +
                         std::to_string(myRepeatMonths) + " mths";
    return retStr;
}

int ScheduledMaintEvent::getRepeatOdom() const
{
    return myRepeatOdom;
}

void ScheduledMaintEvent::setRepeatOdom(int odom)
{
    myRepeatOdom = odom;
}

int ScheduledMaintEvent::getRepeatMonths() const
{
    return myRepeatMonths;
}

void  ScheduledMaintEvent::setRepeatMonths(int months)
{
    myRepeatMonths = months;
}

ScheduledMaintTypes::ScheduledMaintType ScheduledMaintEvent::getMaintType() const
{
    return myMaintType;
}

void ScheduledMaintEvent::setMaintType(ScheduledMaintTypes::ScheduledMaintType mType)
{
    myMaintType = mType;
}

std::string ScheduledMaintEvent::getMaintTypeAsString(ScheduledMaintTypes::ScheduledMaintType mType)
{
    std::string retStr;
    switch (mType)
    {
    case ScheduledMaintTypes::DRIVE_BELTS:
        retStr = "DRIVE_BELTS";
        break;
    case ScheduledMaintTypes::OIL_FILTER:
        retStr = "OIL_FILTER";
        break;
    case ScheduledMaintTypes::COOLANT_FLUSH:
        retStr = "COOLANT_FLUSH";
        break;
    case ScheduledMaintTypes::AIR_FILTER:
        retStr = "AIR_FILTER";
        break;
    case ScheduledMaintTypes::LINES_AND_HOSES:
        retStr = "LINES_AND_HOSES";
        break;
    case ScheduledMaintTypes::SPARK_PLUGS:
        retStr = "SPARK_PLUGS";
        break;
    case ScheduledMaintTypes::BRAKES:
        retStr = "BRAKES";
        break;
    case ScheduledMaintTypes::CABIN_AIR_FILTER:
        retStr = "CABIN_AIR_FILTER";
        break;
    case ScheduledMaintTypes::OTHER:
        retStr = "OTHER";
        break;
    default:
    case ScheduledMaintTypes::NoType:
        retStr = "NoType";
        break;
    }

    return retStr;
}

ScheduledMaintTypes::ScheduledMaintType ScheduledMaintEvent::getMaintTypeFromString(const std::string& strType)
{
    ScheduledMaintTypes::ScheduledMaintType retType = ScheduledMaintTypes::NoType;

    if (strType == "DRIVE_BELTS")
    {
        retType = ScheduledMaintTypes::DRIVE_BELTS;
    }
    else if (strType == "OIL_FILTER")
    {
        retType = ScheduledMaintTypes::OIL_FILTER;
    }
    else if (strType == "COOLANT_FLUSH")
    {
        retType = ScheduledMaintTypes::COOLANT_FLUSH;
    }
    else if (strType == "AIR_FILTER")
    {
        retType = ScheduledMaintTypes::AIR_FILTER;
    }
    else if (strType == "LINES_AND_HOSES")
    {
        retType = ScheduledMaintTypes::LINES_AND_HOSES;
    }
    else if (strType == "SPARK_PLUGS")
    {
        retType = ScheduledMaintTypes::SPARK_PLUGS;
    }
    else if (strType == "BRAKES")
    {
        retType = ScheduledMaintTypes::BRAKES;
    }
    else if (strType == "CABIN_AIR_FILTER")
    {
        retType = ScheduledMaintTypes::CABIN_AIR_FILTER;
    }
    else if (strType == "OTHER")
    {
        retType = ScheduledMaintTypes::OTHER;
    }

    return retType;
}

bool ScheduledMaintEvent::operator==(const ScheduledMaintEvent& rhs)
{
    if (&rhs == this) return true;      // Check for compare to self...

    // Compare all base class bits...
    if (!ServiceEventBase::operator==(rhs))
        return false;

    // Now all derived bits...
    if (getRepeatOdom() != rhs.getRepeatOdom())
        return false;
    if (getRepeatMonths() != rhs.getRepeatMonths())
        return false;
    if (getMaintType() != rhs.getMaintType())
        return false;

    return true;
}

bool ScheduledMaintEvent::operator!=(const ScheduledMaintEvent& rhs)
{
    return !(*this == rhs);
}

// Friend, non-member func...
std::ostream& operator<<(std::ostream& os, const ScheduledMaintEvent& v)
{
    // Print the base-class bits...
    os << dynamic_cast<const ServiceEventBase&>(v);

    // Now add this classes extras...
    os << v.getRepeatOdom()   << ","
       << v.getRepeatMonths() << ","
       << ScheduledMaintEvent::getMaintTypeAsString(v.getMaintType()) << ",";

    return os;
}
